/******************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : NB_UL_FFT.c
* Description : 512 point FFT
* Comments    : NONE
******************************************************************************/

/** STANDARD INCLUDES ********************************************************/
#include <math.h>

/** PROJECT INCLUDES *********************************************************/
#include "NB_UL_FFT.h"

/******************************************************************************
* Function              : cplx16_Mul().
* Description           : This function is used for Complex multiplication
* Input parameters      : cplx16Num1,cplx16Num2
* Output parameters     : Complex conjugate multiplication output
* Called functions      : NONE
* Return value          : cplx16result : 32-bit  Complex output
* Exception             : NONE
******************************************************************************/

CPLX16 cplx16_Mul(CPLX16 cplx16Num1, CPLX16 cplx16Num2,UINT32 ui32NumSf,UINT8 ui8ScalVal)
{
    CPLX32 cplx32num1,cplx32num2, cplx32Res;
    CPLX16 cplx16result;

    cplx32num1.real = cplx16Num1.real;
    cplx32num1.imag = cplx16Num1.imag;

    if((ui32NumSf % 2) == 0)
    {
        cplx32num2.real = -(cplx16Num2.real);
        cplx32num2.imag = -(cplx16Num2.imag);
    }
    else
    {
        cplx32num2.real = cplx16Num2.real;
        cplx32num2.imag = cplx16Num2.imag;
    }

    cplx32Res.real = (((cplx32num1.real * cplx32num2.real)) - ((cplx32num1.imag * cplx32num2.imag))) ;
    cplx32Res.imag = (((cplx32num1.real * cplx32num2.imag)) + ((cplx32num2.real * cplx32num1.imag))) ;

    cplx16result.real = cplx32Res.real >> ui8ScalVal;
    cplx16result.imag = cplx32Res.imag >> ui8ScalVal;

    return cplx16result;

}


/******************************************************************************
* Function              : NBIOT_FFTshift()
* Description           : This function performs fft shift
* Input parameters      : pcplx16Inp  : Pointer to the input buffer
*                         ui16FftSize : fft size
* Output parameters     : NONE
* Called functions      : NONE
* Return value          : NONE
* Exception             : NONE
******************************************************************************/

void NB_ENB_FFTshift(CPLX16 *pcplx16Input, UINT16 ui16FftSize)
{

    UINT16 ui16Index1=0,ui16Length = ui16FftSize >> 1;
    CPLX16 pcplx16Temp= {0,0};

    for(ui16Index1= 0; ui16Index1 < ui16Length; ui16Index1++)
    {
        pcplx16Temp = pcplx16Input[ui16Length + ui16Index1];
        pcplx16Input[ui16Length + ui16Index1] = pcplx16Input[ui16Index1];
        pcplx16Input[ui16Index1] = pcplx16Temp;
    }
}

/******************************************************************************
* Function              : NBIOT_UL_FFT()
* Description           : Performs fft operation
* Input parameters      : pcplx16Inp    : pointer to input buffer
*                         pcplx16Output : pointer to output buffer
*                         ui16Fftsize   : fft size
* Output parameters     : NONE
* Called functions      : gen_twiddle_fft16x16()
*                         DSP_fft16x16_cn
* Return value          : NONE
* Exception             : NONE
******************************************************************************/
void NBIOT_UL_FFT(CPLX16 *pcplx16Inp,CPLX16 *pcplx16Output, UINT16 ui16Fftsize,UINT8 ui8Inlen)
{
    INT16 ai16TwiddleFactor[1024] = {0};
    INT32 i32twiddleOffset = 0;
    CPLX16 acplx16TempFftInputBuffer[512];
    CPLX16 acplx16TempFftOutputBuffer[512];
    memset(acplx16TempFftInputBuffer,   0,sizeof(CPLX16)*512);
    memset(acplx16TempFftOutputBuffer,   0,sizeof(CPLX16)*512);

    memcpy(acplx16TempFftInputBuffer,pcplx16Inp,ui8Inlen*sizeof(CPLX16));

    i32twiddleOffset = gen_twiddle_fft16x16(ai16TwiddleFactor, ui16Fftsize);

    DSP_fft16x16_cn (ai16TwiddleFactor,ui16Fftsize,acplx16TempFftInputBuffer,acplx16TempFftOutputBuffer);

    memcpy(pcplx16Output,acplx16TempFftOutputBuffer,ui16Fftsize*sizeof(CPLX16));

}

/****** FFT ********/
#ifndef PI
# ifdef M_PI
#  define PI M_PI
# else
#  define PI 3.14159265358979323846
# endif
#endif

# define DIG_REV(i, m, j)                                                   \
    do {                                                                    \
        unsigned _ = (i);                                                   \
        _ = ((_ & 0x33333333) <<  2) | ((_ & ~0x33333333) >>  2);           \
        _ = ((_ & 0x0F0F0F0F) <<  4) | ((_ & ~0x0F0F0F0F) >>  4);           \
        _ = ((_ & 0x00FF00FF) <<  8) | ((_ & ~0x00FF00FF) >>  8);           \
        _ = ((_ & 0x0000FFFF) << 16) | ((_ & ~0x0000FFFF) >> 16);           \
        (j) = _ >> (m);                                                     \
    } while (0)

static short d2s(double d)
{
    d = floor(0.5 + d);  // Explicit rounding to integer //
    if (d >=  32767.0) return  32767;
    if (d <= -32768.0) return -32768;
    return (short)d;
}


void DSP_fft16x16_cn (
    const short * ptr_w,
    int npoints,
    short * ptr_x,
    short * ptr_y
)
{

    const short *w;
    short * x, * x2, * x0;
    short * y0, * y1, * y2, *y3;

    short xt0_0, yt0_0, xt1_0, yt1_0, xt2_0, yt2_0;
    short xt0_1, yt0_1, xt1_1, yt1_1, xt2_1, yt2_1;
    short xh0_0, xh1_0, xh20_0, xh21_0, xl0_0, xl1_0, xl20_0, xl21_0;
    short xh0_1, xh1_1, xh20_1, xh21_1, xl0_1, xl1_1, xl20_1, xl21_1;
    short x_0, x_1, x_2, x_3, x_l1_0, x_l1_1, x_l1_2, x_l1_3, x_l2_0, x_l2_1;
    short xh0_2, xh1_2, xl0_2, xl1_2, xh0_3, xh1_3, xl0_3, xl1_3;
    short x_4, x_5, x_6, x_7, x_l2_2, x_l2_3, x_h2_0, x_h2_1, x_h2_2, x_h2_3;
    short x_8, x_9, x_a, x_b, x_c, x_d, x_e, x_f;
    short si10, si20, si30, co10, co20, co30;
    short si11, si21, si31, co11, co21, co31;
    short n00, n10, n20, n30, n01, n11, n21, n31;
    short n02, n12, n22, n32, n03, n13, n23, n33;
    short n0, j0;

    int i, j, l1, l2, h2, predj, tw_offset, stride, fft_jmp;
    int radix, norm, m;

    /*---------------------------------------------------------------------*/
    /* Determine the magnitude od the number of points to be transformed.  */
    /* Check whether we can use a radix4 decomposition or a mixed radix    */
    /* transformation, by determining modulo 2.                            */
    /*---------------------------------------------------------------------*/
    for (i = 31, m = 1; (npoints & (1 << i)) == 0; i--, m++)
        ;
    norm = m - 2;
    radix = m & 1 ? 2 : 4;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 6*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/

    stride = npoints;
    tw_offset = 0;
    fft_jmp = 6 * stride;

    #ifndef NOASSUME
//    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);
    #endif

    while (stride > 4) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 6 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          6 N/4               1               */
        /*  2                          6 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/
        j = 0;
        fft_jmp >>= 2;

        /*-----------------------------------------------------------------*/
        /* Set up offsets to access "N/4", "N/2", "3N/4" complex point or  */
        /* "N/2", "N", "3N/2" half word                                    */
        /*-----------------------------------------------------------------*/
        h2 = stride >> 1;
        l1 = stride;
        l2 = stride + (stride >> 1);

        /*-----------------------------------------------------------------*/
        /*  Reset "x" to point to the start of the input data array.       */
        /* "tw_offset" starts off at 0, and increments by "6 * stride"     */
        /*  The stride quarters with every iteration of the outer loop     */
        /*-----------------------------------------------------------------*/
        x = ptr_x;
        w = ptr_w + tw_offset;
        tw_offset += fft_jmp;
        stride  >>= 2;

        /*----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies, */
        /* within a given stage. Recall that there are logN to base 4     */
        /* stages. Certain butterflies share the twiddle factors. These   */
        /* are grouped together. On the very first stage there are no     */
        /* butterflies that share the twiddle factor, all N/4 butter-     */
        /* flies have different factors. On the next stage two sets of    */
        /* N/8 butterflies share the same twiddle factor. Hence after     */
        /* half the butterflies are performed, j the index into the       */
        /* factor array resets to 0, and the twiddle factors are reused.  */
        /* When this happens, the data pointer 'x' is incremented by the  */
        /* fft_jmp amount. In addition the following code is unrolled to  */
        /* perform "2" radix4 butterflies in parallel.                    */
        /*----------------------------------------------------------------*/
        #ifndef NOASSUME
//        _nassert((int)(w) % 8 == 0);
//        _nassert((int)(x) % 8 == 0);
//        _nassert(h2 % 8 == 0);
//        _nassert(l1 % 8 == 0);
//        _nassert(l2 % 8 == 0);
        #pragma MUST_ITERATE(1,,1);
        #endif

        for (i = 0; i < (npoints >> 3); i ++) {
            /*------------------------------------------------------------*/
            /* Read the first 12 twiddle factors, six of which are used   */
            /* for one radix 4 butterfly and six of which are used for    */
            /* next one.                                                  */
            /*------------------------------------------------------------*/

#ifdef _LITTLE_ENDIAN
            // twiddle factors for first butterfly
            co10 = w[j+1];
            si10 = w[j+0];
            co20 = w[j+5];
            si20 = w[j+4];
            co30 = w[j+9];
            si30 = w[j+8];

            // twiddle factors for second butterfly
            co11 = w[j+3];
            si11 = w[j+2];
            co21 = w[j+7];
            si21 = w[j+6];
            co31 = w[j+11];
            si31 = w[j+10];
#else
            co10 = w[j+0];
            si10 = -w[j+1];
            co20 = w[j+4];
            si20 = -w[j+5];
            co30 = w[j+8];
            si30 = -w[j+9];

            // twiddle factors for second butterfly
            co11 = w[j+2];
            si11 = -w[j+3];
            co21 = w[j+6];
            si21 = -w[j+7];
            co31 = w[j+10];
            si31 = -w[j+11];
#endif
            /*------------------------------------------------------------*/
            /* Read in the first complex input for the butterflies.       */
            /* 1st complex input to 1st butterfly: x[0] + jx[1]           */
            /* 1st complex input to 2nd butterfly: x[2] + jx[3]           */
            /*------------------------------------------------------------*/
            x_0 = x[0];  // Re[x(k)]
            x_1 = x[1];  // Im[x(k)]
            x_2 = x[2];  // second butterfly
            x_3 = x[3];

            /*------------------------------------------------------------*/
            /* Read in the complex inputs for the butterflies. Each of the*/
            /* successive complex inputs of the butterfly are seperated   */
            /* by a fixed amount known as stride. The stride starts out   */
            /* at N/4, and quarters with every stage.                     */
            /*------------------------------------------------------------*/
            x_l1_0 = x[l1  ]; // Re[x(k+N/2)]
            x_l1_1 = x[l1+1]; // Im[x(k+N/2)]
            x_l1_2 = x[l1+2]; // second butterfly
            x_l1_3 = x[l1+3];

            x_l2_0 = x[l2  ]; // Re[x(k+3*N/2)]
            x_l2_1 = x[l2+1]; // Im[x(k+3*N/2)]
            x_l2_2 = x[l2+2]; // second butterfly
            x_l2_3 = x[l2+3];

            x_h2_0 = x[h2  ]; // Re[x(k+N/4)]
            x_h2_1 = x[h2+1]; // Im[x(k+N/4)]
            x_h2_2 = x[h2+2]; // second butterfly
            x_h2_3 = x[h2+3];

            /*-----------------------------------------------------------*/
            /* Two butterflies are evaluated in parallel. The following  */
            /* results will be shown for one butterfly only, although    */
            /* both are being evaluated in parallel.                     */
            /*                                                           */
            /* Perform radix2 style DIF butterflies.                     */
            /*-----------------------------------------------------------*/
            xh0_0 = x_0 + x_l1_0;    xh1_0 = x_1 + x_l1_1;
            xh0_1 = x_2 + x_l1_2;    xh1_1 = x_3 + x_l1_3;

            xl0_0 = x_0 - x_l1_0;    xl1_0 = x_1 - x_l1_1;
            xl0_1 = x_2 - x_l1_2;    xl1_1 = x_3 - x_l1_3;

            xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;
            xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;

            xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;
            xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x0 = x;
            x2 = x0;

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 12, to reflect the fact that 12 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 12;
            x += 4;

            predj = (j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;

            /*----------------------------------------------------------*/
            /* These four partial results can be re-written to show     */
            /* the underlying DIF structure similar to radix2 as        */
            /* follows:                                                 */
            /*                                                          */
            /* X(4k)  = (x(n)+x(n + N/2)) + (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+1)= (x(n)-x(n + N/2)) -j(x(n+N/4) - x(n + 3N/4))    */
            /* x(4k+2)= (x(n)+x(n + N/2)) - (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+3)= (x(n)-x(n + N/2)) +j(x(n+N/4) - x(n + 3N/4))    */
            /*                                                          */
            /* which leads to the real and imaginary values as foll:    */
            /*                                                          */
            /* y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20           */
            /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21           */
            /* y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21           */
            /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20           */
            /* y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20           */
            /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21           */
            /* y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21           */
            /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20           */
            /* ---------------------------------------------------------*/
            x0[0] = (xh0_0 + xh20_0 + 1) >> 1;
            x0[1] = (xh1_0 + xh21_0 + 1) >> 1;
            x0[2] = (xh0_1 + xh20_1 + 1) >> 1;
            x0[3] = (xh1_1 + xh21_1 + 1) >> 1;

            xt0_0 = xh0_0 - xh20_0;
            yt0_0 = xh1_0 - xh21_0;
            xt0_1 = xh0_1 - xh20_1;
            yt0_1 = xh1_1 - xh21_1;

            xt1_0 = xl0_0 + xl21_0;
            yt2_0 = xl1_0 + xl20_0;
            xt2_0 = xl0_0 - xl21_0;
            yt1_0 = xl1_0 - xl20_0;

            xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;
            xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;

            /*---------------------------------------------------------*/
            /* Perform twiddle factor multiplies of three terms,top    */
            /* term does not have any multiplies. Note the twiddle     */
            /* factors for a normal FFT are C + j (-S). Since the      */
            /* factors that are stored are C + j S, this is            */
            /* corrected for in the multiplies.                        */
            /*                                                         */
            /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)       */
            /*---------------------------------------------------------*/
            x2[l1  ] = (-co20 * xt0_0 - si20 * yt0_0 + 0x8000) >> 16;
            x2[l1+1] = (-co20 * yt0_0 + si20 * xt0_0 + 0x8000) >> 16;

            x2[l1+2] = (-co21 * xt0_1 - si21 * yt0_1 + 0x8000) >> 16;
            x2[l1+3] = (-co21 * yt0_1 + si21 * xt0_1 + 0x8000) >> 16;

            x2[h2  ] = (co10 * xt1_0 + si10 * yt1_0 + 0x8000) >> 16;
            x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0 + 0x8000) >> 16;

            x2[h2+2] = (co11 * xt1_1 + si11 * yt1_1 + 0x8000) >> 16;
            x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1 + 0x8000) >> 16;

            x2[l2  ] = (co30 * xt2_0 + si30 * yt2_0 + 0x8000) >> 16;
            x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0 + 0x8000) >> 16;

            x2[l2+2] = (co31 * xt2_1 + si31 * yt2_1 + 0x8000) >> 16;
            x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1 + 0x8000) >> 16;
        }
    }

    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/4, N/2, 3N/4 for a radix4 FFT, and 0, N/8    */
    /* N/2, 3N/8 for radix 2.                                          */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + (int)npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int)(npoints >> 1);

    if (radix == 2) {
        /*----------------------------------------------------------------*/
        /* The pointers are set at the following locations which are half */
        /* the offsets of a radix4 FFT.                                   */
        /*----------------------------------------------------------------*/
        y1 = y0 + (int)(npoints >> 2);
        y3 = y2 + (int)(npoints >> 2);
        l1 = norm + 1;
        j0 = 8;
        n0 = npoints >> 1;
    }
    else {
        y1 = y0 + (int)(npoints >> 1);
        y3 = y2 + (int)(npoints >> 1);
        l1 = norm + 2;
        j0 = 4;
        n0 = npoints >> 2;
    }

    /*--------------------------------------------------------------------*/
    /* The following code reads data indentically for either a radix 4    */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/
    j = 0;

    #ifndef NOASSUME
//    _nassert((int)(n0) % 4  == 0);
//    _nassert((int)(x0) % 8 == 0);
//    _nassert((int)(x2) % 8 == 0);
//    _nassert((int)(y0) % 8 == 0);
    #pragma MUST_ITERATE(2,,2);
    #endif

    for (i = 0; i < npoints; i += 8) {
        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/
        DIG_REV(j, l1, h2);

        /*----------------------------------------------------------------*/
        /* Read in the input data, from the first eight locations. These  */
        /* are transformed either as a radix4 or as a radix 2.            */
        /*----------------------------------------------------------------*/
        x_0 = x0[0];
        x_1 = x0[1];
        x_2 = x0[2];
        x_3 = x0[3];
        x_4 = x0[4];
        x_5 = x0[5];
        x_6 = x0[6];
        x_7 = x0[7];
        x0 += 8;

        xh0_0 = x_0 + x_4;
        xh1_0 = x_1 + x_5;
        xl0_0 = x_0 - x_4;
        xl1_0 = x_1 - x_5;
        xh0_1 = x_2 + x_6;
        xh1_1 = x_3 + x_7;
        xl0_1 = x_2 - x_6;
        xl1_1 = x_3 - x_7;

        n00 = xh0_0 + xh0_1;
        n01 = xh1_0 + xh1_1;
        n10 = xl0_0 + xl1_1;
        n11 = xl1_0 - xl0_1;
        n20 = xh0_0 - xh0_1;
        n21 = xh1_0 - xh1_1;
        n30 = xl0_0 - xl1_1;
        n31 = xl1_0 + xl0_1;

        if (radix == 2) {
            /*-------------------------------------------------------------*/
            /* Perform radix2 style decomposition.                         */
            /*-------------------------------------------------------------*/
            n00 = x_0 + x_2;
            n01 = x_1 + x_3;
            n20 = x_0 - x_2;
            n21 = x_1 - x_3;
            n10 = x_4 + x_6;
            n11 = x_5 + x_7;
            n30 = x_4 - x_6;
            n31 = x_5 - x_7;
        }

        y0[2*h2] = n00;
        y0[2*h2 + 1] = n01;
        y1[2*h2] = n10;
        y1[2*h2 + 1] = n11;
        y2[2*h2] = n20;
        y2[2*h2 + 1] = n21;
        y3[2*h2] = n30;
        y3[2*h2 + 1] = n31;

        /*----------------------------------------------------------------*/
        /* Read in ht enext eight inputs, and perform radix4 or radix2    */
        /* decomposition.                                                 */
        /*----------------------------------------------------------------*/
        x_8 = x2[0];    x_9 = x2[1];
        x_a = x2[2];    x_b = x2[3];
        x_c = x2[4];    x_d = x2[5];
        x_e = x2[6];    x_f = x2[7];
        x2 += 8;

        xh0_2 = x_8 + x_c;    xh1_2 = x_9 + x_d;
        xl0_2 = x_8 - x_c;    xl1_2 = x_9 - x_d;
        xh0_3 = x_a + x_e;    xh1_3 = x_b + x_f;
        xl0_3 = x_a - x_e;    xl1_3 = x_b - x_f;

        n02 = xh0_2 + xh0_3;    n03 = xh1_2 + xh1_3;
        n12 = xl0_2 + xl1_3;    n13 = xl1_2 - xl0_3;
        n22 = xh0_2 - xh0_3;    n23 = xh1_2 - xh1_3;
        n32 = xl0_2 - xl1_3;    n33 = xl1_2 + xl0_3;

        if (radix == 2) {
            n02 = x_8 + x_a;    n03 = x_9 + x_b;
            n22 = x_8 - x_a;    n23 = x_9 - x_b;
            n12 = x_c + x_e;    n13 = x_d + x_f;
            n32 = x_c - x_e;    n33 = x_d - x_f;
        }

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/4]  */
        /* y[N/2], y[3N/4] in a radix4 scheme, y, y[N/8], y[N/2],y[5N/8]   */
        /*-----------------------------------------------------------------*/
        y0[2*h2+2] = n02;    y0[2*h2+3] = n03;
        y1[2*h2+2] = n12;    y1[2*h2+3] = n13;
        y2[2*h2+2] = n22;    y2[2*h2+3] = n23;
        y3[2*h2+2] = n32;    y3[2*h2+3] = n33;

        j += j0;
        if (j == n0) {
            j += n0;
            x0 += (int)npoints >> 1;
            x2 += (int)npoints >> 1;
        }
    }

    for(i=0;i<2*npoints;i++)
    {
        ptr_y[i] = ptr_y[i]<<1;
    }
}

int gen_twiddle_fft16x16(short *wout, int n)
{
    int i, j, k;
    double M = 32767.5;

    for (j = 1, k = 0; j < n >> 2; j = j << 2) {
        for (i = 0; i < n >> 2; i += j << 1) {
            wout[k + 11] = -d2s(M * sin(6.0 * PI * (i + j) / n));
            wout[k + 10] =  d2s(M * cos(6.0 * PI * (i + j) / n));
            wout[k +  9] = -d2s(M * sin(6.0 * PI * (i    ) / n));
            wout[k +  8] =  d2s(M * cos(6.0 * PI * (i    ) / n));

            wout[k +  7] = d2s(M * sin(4.0 * PI * (i + j) / n));
            wout[k +  6] = -d2s(M * cos(4.0 * PI * (i + j) / n));
            wout[k +  5] = d2s(M * sin(4.0 * PI * (i    ) / n));
            wout[k +  4] = -d2s(M * cos(4.0 * PI * (i    ) / n));

            wout[k +  3] = -d2s(M * sin(2.0 * PI * (i + j) / n));
            wout[k +  2] =  d2s(M * cos(2.0 * PI * (i + j) / n));
            wout[k +  1] = -d2s(M * sin(2.0 * PI * (i    ) / n));
            wout[k +  0] =  d2s(M * cos(2.0 * PI * (i    ) / n));

            k += 12;
        }
    }
    return k;
}


/********************** End of file NB_UL_FFT.c ***********************/
