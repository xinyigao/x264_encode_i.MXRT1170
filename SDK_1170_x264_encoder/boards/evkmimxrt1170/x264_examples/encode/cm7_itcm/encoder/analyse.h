/*****************************************************************************
 * analyse.h: macroblock analysis
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

#ifndef X264_ANALYSE_H
#define X264_ANALYSE_H

#include "common/common.h"
#include "macroblock_encoder.h"
#include "me.h"
#include "ratecontrol.h"

typedef struct
{
    x264_me_t me16x16;
    x264_me_t bi16x16;      /* for b16x16 BI mode, since MVs can differ from l0/l1 */
    x264_me_t me8x8[4];
    x264_me_t me4x4[4][4];
    x264_me_t me8x4[4][2];
    x264_me_t me4x8[4][2];
    x264_me_t me16x8[2];
    x264_me_t me8x16[2];
    int i_rd16x16;
    int i_cost8x8;
    int i_cost4x4[4]; /* cost per 8x8 partition */
    int i_cost8x4[4]; /* cost per 8x8 partition */
    int i_cost4x8[4]; /* cost per 8x8 partition */
    int i_cost16x8;
    int i_cost8x16;
    /* [ref][0] is 16x16 mv, [ref][1..4] are 8x8 mv from partition [0..3] */
    ALIGNED_4( int16_t mvc[32][5][2] );
} x264_mb_analysis_list_t;

typedef struct
{
    /* conduct the analysis using this lamda and QP */
    int i_lambda;
    int i_lambda2;
    int i_qp;
    uint16_t *p_cost_mv;
    uint16_t *p_cost_ref[2];
    int i_mbrd;


    /* I: Intra part */
    /* Take some shortcuts in intra search if intra is deemed unlikely */
    int b_fast_intra;
    int b_force_intra; /* For Periodic Intra Refresh.  Only supported in P-frames. */
    int b_avoid_topright; /* For Periodic Intra Refresh: don't predict from top-right pixels. */
    int b_try_skip;

    /* Luma part */
    int i_satd_i16x16;
    int i_satd_i16x16_dir[7];
    int i_predict16x16;

    int i_satd_i8x8;
    int i_cbp_i8x8_luma;
    ALIGNED_16( uint16_t i_satd_i8x8_dir[4][16] );
    int i_predict8x8[4];

    int i_satd_i4x4;
    int i_predict4x4[16];

    int i_satd_pcm;

    /* Chroma part */
    int i_satd_chroma;
    int i_satd_chroma_dir[7];
    int i_predict8x8chroma;

    /* II: Inter part P/B frame */
    x264_mb_analysis_list_t l0;
    x264_mb_analysis_list_t l1;

    int i_cost16x16bi; /* used the same ref and mv as l0 and l1 (at least for now) */
    int i_cost16x16direct;
    int i_cost8x8bi;
    int i_cost8x8direct[4];
    int i_satd8x8[3][4]; /* [L0,L1,BI][8x8 0..3] SATD only */
    int i_cost_est16x8[2]; /* Per-partition estimated cost */
    int i_cost_est8x16[2];
    int i_cost16x8bi;
    int i_cost8x16bi;
    int i_rd16x16bi;
    int i_rd16x16direct;
    int i_rd16x8bi;
    int i_rd8x16bi;
    int i_rd8x8bi;

    int i_mb_partition16x8[2]; /* mb_partition_e */
    int i_mb_partition8x16[2];
    int i_mb_type16x8; /* mb_class_e */
    int i_mb_type8x16;

    int b_direct_available;
    int b_early_terminate;

} x264_mb_analysis_t;

int x264_analyse_init_costs( x264_t *h );
void x264_analyse_free_costs( x264_t *h );
void x264_analyse_weight_frame( x264_t *h, int end );
void x264_macroblock_analyse( x264_t *h );
void x264_slicetype_decide( x264_t *h );

//void x264_slicetype_analyse( x264_t *h, int intra_minigop );

int  x264_lookahead_init( x264_t *h, int i_slicetype_length );
int  x264_lookahead_is_empty( x264_t *h );
void x264_lookahead_put_frame( x264_t *h, x264_frame_t *frame );
void x264_lookahead_get_frames( x264_t *h );
void x264_lookahead_delete( x264_t *h );
void x264_mb_analyse_load_costs( x264_t *h, x264_mb_analysis_t *a );
#endif
