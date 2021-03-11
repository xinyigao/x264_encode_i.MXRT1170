/*****************************************************************************
 * raw.c: raw muxer
 *****************************************************************************
 * Copyright (C) 2003-2017 x264 project
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *          Loren Merritt <lorenm@u.washington.edu>
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
/***************************************************************************************************************************************/
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

#include "pin_mux.h"
#include "clock_config.h"
/***************************************************************************************************************************************/


#include "output.h"

AT_NONCACHEABLE_SECTION(static FIL txtFil_1);

UINT* bwwww;
UINT* bw_wh;
UINT* bw_wf;
char buf1[100];
FRESULT fr_1;
FRESULT fr_2;
FRESULT fr_3;
FRESULT fr_4;
FRESULT res;
int i=0;

FSIZE_t res_size;
static int open_file( char *psz_filename, hnd_t *p_handle, cli_output_opt_t *opt )
{
  
  fr_1 = f_open(&txtFil_1,_T("/test.h264"),FA_WRITE | FA_CREATE_ALWAYS);
  PRINTF("open_file.test.h264\n");
    return 0;
}

static int set_param( hnd_t handle, x264_param_t *p_param )
{
    return 0;
}

static int write_headers( hnd_t handle, x264_nal_t *p_nal )
{
    int size = p_nal[0].i_payload + p_nal[1].i_payload + p_nal[2].i_payload;

   // if( fwrite( p_nal[0].p_payload, size, 1, (FILE*)handle ) )
      if( f_write( (FIL*)handle ,p_nal[0].p_payload, size, bw_wh ))
      {
        PRINTF(" f_write success header\r\n");
        return size;
      }
     return -1;
}

static int write_frame( hnd_t handle, uint8_t *p_nalu, int i_size, x264_picture_t *p_picture )
{

       fr_4 =f_write(&txtFil_1,p_nalu,i_size,bw_wf );
        if(fr_4)
        {  
          PRINTF(" write test.h264 error value: %d %d\r\n",fr_4,bw_wf);
 //         break;
        }

    return i_size;
 //   return -1;
}

static int close_file( hnd_t handle, int64_t largest_pts, int64_t second_largest_pts )
{
   PRINTF("close_file\r\n");
   f_close(&txtFil_1);
   PRINTF("close_file1\r\n");

const cli_output_t raw_output = { open_file, set_param, write_headers, write_frame, close_file };

