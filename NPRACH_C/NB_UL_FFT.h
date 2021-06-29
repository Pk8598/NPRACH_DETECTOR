/******************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : NB_UL_FFT.h
* Description : File contains FFT16x16 prototypesfor uplink
* Comments    :
******************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NB_DataTypes.h"

/** FILE GUARDS **************************************************************/
#ifndef NB_UL_FFT_H_INCLUDED
#define NB_UL_FFT_H_INCLUDED

/** MACRO AND TYPE DEFINITIONS ***********************************************/

#define     DELTAF_15KHZ                                     (15000)
#define     DELTAF_3750                                      (3750)
#define     FFT_SIZE_UPLINK_15KHZ                            (16)
#define     FFT_SIZE_UPLINK_3750                             (64)
#define     NUM_SUBCARR_UL_3750                              (48)
#define     NUM_SYMBOL_IN_SUB_FRAME                          (14)
#define     NUM_SYMBOL_IN_SLOT                               (NUM_SYMBOL_IN_SUB_FRAME/2)
#define     DEC_FACTOR                                       (8)
#define     NUM_SUBCARR_UL_15KHZ                             (12) /* N_SC_RM */


/** FUNCTION PROTOTYPES ***********************************************/

void NB_ENB_FFTshift(CPLX16 *pcplx16Input, UINT16 ui16FftSize);

void NBIOT_UL_FFT(CPLX16 *pcplx16Inp,CPLX16 *pcplx16Output, UINT16 ui16Fftsize,UINT8 ui8Inlen);

int gen_twiddle_fft16x16 (
    short *w,
    int n
);

void DSP_fft16x16_cn (
    const short * ptr_w,
    int npoints,
    short * ptr_x,
    short * ptr_y
);

void NB_ENB_ProcessFFT(CPLX16 *gpcplx16UeRxFFToutput,CPLX16 *pcplx16DownsampledSeq, UINT16 ui16Scs);

void NBULFFt2(CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16M1, UINT16 ui16M2, UINT16 ui16Nrows, UINT16 ui16Ncols);

#endif

/********************** End of header file NB_UL_FFT.h ***********************/
