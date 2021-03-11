/*****************************************************************************
 * raw.c: raw input
 *****************************************************************************
 * Copyright (C) 2003-2017 x264 project
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *          Loren Merritt <lorenm@u.washington.edu>
 *          Steven Walters <kemuri9@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_cache.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

#include "board.h"

#include "input.h"
#include "data.h"
#define FAIL_IF_ERROR( cond, ... ) FAIL_IF_ERR( cond, "raw", __VA_ARGS__ )


AT_NONCACHEABLE_SECTION(static FIL txtFil_2);

UINT* bw_yuv;

FRESULT fr_open_yuv;
//
//AT_NONCACHEABLE_SECTION(static FATFS g_fileSystem); /* File system object */
//
//static const sdmmchost_detect_card_t s_sdCardDetect = {
//#ifndef BOARD_SD_DETECT_TYPE
//    .cdType = kSDMMCHOST_DetectCardByGpioCD,
//#else
//    .cdType = BOARD_SD_DETECT_TYPE,
//#endif
//    .cdTimeOut_ms = (~0U),
//};
//
//
///***************************************************************************************************************************************/ 
//static status_t sdcardWaitCardInsert(void)
//{
//    /* Save host information. */
//    g_sd.host.base = SD_HOST_BASEADDR;
//    g_sd.host.sourceClock_Hz = SD_HOST_CLK_FREQ;
//    /* card detect type */
//    g_sd.usrParam.cd = &s_sdCardDetect;
//    /* SD host init function */
//    if (SD_HostInit(&g_sd) != kStatus_Success)
//    {
//        PRINTF("\r\nSD host init fail\r\n");
//        return kStatus_Fail;
//    }
//    /* power off card */
//    SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr);
//    /* wait card insert */
//    if (SD_WaitCardDetectStatus(SD_HOST_BASEADDR, &s_sdCardDetect, true) == kStatus_Success)
//    {
//        PRINTF("\r\nCard inserted.\r\n");
//        /* power on the card */
//        SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);
//    }
//    else
//    {
//        PRINTF("\r\nCard detect fail.\r\n");
//        return kStatus_Fail;
//    }
//
//    return kStatus_Success;
//}
///***************************************************************************************************************************************/ 
//
//static int MOUNT_SDCard(void)
//{
//    FRESULT error;
//    const TCHAR driverName[3U] = {SDDISK + '0', ':', '/'};
//
//    // clear FATFS manually
//    memset((void *)&g_fileSystem, 0, sizeof(g_fileSystem));
//
//    /* Wait for the card insert. */
//    if (sdcardWaitCardInsert() != kStatus_Success)
//    {
//        PRINTF("Card not inserted.\r\n");
//        return -1;
//    }
//
//    // Mount the driver
//    if (f_mount(&g_fileSystem, driverName, 0))
//    {
//        PRINTF("Mount volume failed.\r\n");
//        return -2;
//    }
//
//#if (_FS_RPATH >= 2U)
//    if (f_chdrive((char const *)&driverName[0U]))
//    {
//        PRINTF("Change drive failed.\r\n");
//        return -3;
//    }
//#endif
//
//    return 0;
//}
//
//
//
//


typedef struct
{
    //FILE *fh;
    int next_frame;
    uint64_t plane_size[4];
    uint64_t frame_size;
    int bit_depth;
    cli_mmap_t mmap;
    int use_mmap;
} raw_hnd_t;

static int open_file( char *psz_filename, hnd_t *p_handle, video_info_t *info, cli_input_opt_t *opt )
{
   raw_hnd_t *h = calloc( 1, sizeof(raw_hnd_t) );
 // raw_hnd_t *h = malloc(sizeof(raw_hnd_t) );
    if( !h )
        return -1;

    if( !opt->resolution )
    {
        /* try to parse the file name */
        for( char *p = psz_filename; *p; p++ )
            if( *p >= '0' && *p <= '9' && sscanf( p, "%dx%d", &info->width, &info->height ) == 2 )
                break;
    }
    else
        sscanf( opt->resolution, "%dx%d", &info->width, &info->height );
    FAIL_IF_ERROR( !info->width || !info->height, "raw input requires a resolution.\n" );
    if( opt->colorspace )
    {
        for( info->csp = X264_CSP_CLI_MAX-1; info->csp > X264_CSP_NONE; info->csp-- )
        {
            if( x264_cli_csps[info->csp].name && !strcasecmp( x264_cli_csps[info->csp].name, opt->colorspace ) )
                break;
        }
        FAIL_IF_ERROR( info->csp == X264_CSP_NONE, "unsupported colorspace `%s'\n", opt->colorspace );
    }
    else /* default */
        info->csp = X264_CSP_I420;

    h->bit_depth = opt->bit_depth;
    FAIL_IF_ERROR( h->bit_depth < 8 || h->bit_depth > 16, "unsupported bit depth `%d'\n", h->bit_depth );
    if( h->bit_depth > 8 )
        info->csp |= X264_CSP_HIGH_DEPTH;
/*************************************************************************************************************/
    fr_open_yuv = f_open(&txtFil_2,_T("/test.yuv"),FA_READ | FA_WRITE);
     PRINTF(" open 420p-out.yuv error value: %d\r\n",fr_open_yuv);
/**************************************************************************************************************/    
    info->thread_safe = 1;
    info->num_frames  = 0;
    info->vfr         = 0;

    const x264_cli_csp_t *csp = x264_cli_get_csp( info->csp );
    for( int i = 0; i < csp->planes; i++ )
    {
        h->plane_size[i] = x264_cli_pic_plane_size( info->csp, info->width, info->height, i );
        h->frame_size += h->plane_size[i];
        /* x264_cli_pic_plane_size returns the size in bytes, we need the value in pixels from here on */
        h->plane_size[i] /= x264_cli_csp_depth_factor( info->csp );
    }

    *p_handle = h;
    return 0;
}

static int read_frame_internal( cli_pic_t *pic, raw_hnd_t *h, int bit_depth_uc )
{
    int pixel_depth = x264_cli_csp_depth_factor( pic->img.csp );

    for( int i = 0; i < pic->img.planes; i++ )
    {
        if( h->use_mmap )
        {
            if( i )
                pic->img.plane[i] = pic->img.plane[i-1] + pixel_depth * h->plane_size[i-1];
        }
 //       else if( fread( pic->img.plane[i], pixel_depth, h->plane_size[i], h->fh ) != h->plane_size[i] )
            return -1;

        if( bit_depth_uc )
        {
            /* upconvert non 16bit high depth planes to 16bit using the same
             * algorithm as used in the depth filter. */
            uint16_t *plane = (uint16_t*)pic->img.plane[i];
            uint64_t pixel_count = h->plane_size[i];
            int lshift = 16 - h->bit_depth;
            for( uint64_t j = 0; j < pixel_count; j++ )
                plane[j] = plane[j] << lshift;
        }
    }
    return 0;
}

static int read_frame( cli_pic_t *pic, hnd_t handle, int i_frame )
{
    raw_hnd_t *h = handle;
  
     f_read(&txtFil_2,pic->img.plane[0],h->plane_size[0],bw_yuv);
    // f_lseek(&txtFil_2,(i_frame * h->frame_size+h->plane_size[0]));
     //f_lseek(&txtFil_2,25280);
     f_read(&txtFil_2,pic->img.plane[1],h->plane_size[1],bw_yuv);
    // f_lseek(&txtFil_2,(i_frame * h->frame_size+h->plane_size[0]+h->plane_size[1]));
     f_read(&txtFil_2,pic->img.plane[2],h->plane_size[2],bw_yuv);
      
    /* f_close(&txtFil_2);//调试使用，关闭打开的yuv文件，移到下面close_file中*/           
                
    return 0;
}

static int release_frame( cli_pic_t *pic, hnd_t handle )
{
    raw_hnd_t *h = handle;
    //if( h->use_mmap )
      //  return x264_cli_munmap( &h->mmap, pic->img.plane[0], h->frame_size );
    return 0;
}

static int picture_alloc( cli_pic_t *pic, hnd_t handle, int csp, int width, int height )
{
    raw_hnd_t *h = handle;
    return (h->use_mmap ? x264_cli_pic_init_noalloc : x264_cli_pic_alloc)( pic, csp, width, height );
}

static void picture_clean( cli_pic_t *pic, hnd_t handle )
{
    raw_hnd_t *h = handle;
    if( h->use_mmap )
        memset( pic, 0, sizeof(cli_pic_t) );
    else
        x264_cli_pic_clean( pic );
}

static int close_file( hnd_t handle )
{
    raw_hnd_t *h = handle;

    f_close(&txtFil_2); 
    
    free( h );
    return 0;
}

const cli_input_t raw_input = { open_file, picture_alloc, read_frame, release_frame, picture_clean, close_file };
