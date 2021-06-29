/*
 * File: FFT2_.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 11-Nov-2020 12:16:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "FFT2_.h"
#include "fft.h"
#include "FFT2__emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *X
 *                unsigned short M1
 *                unsigned short M2
 *                emxArray_creal_T *Y
 * Return Type  : void
 */
void FFT2_(const emxArray_creal_T *X, unsigned short M1, unsigned short M2,
           emxArray_creal_T *Y)
{
  int i0;
  int loop_ub;
  int iter_cols;
  emxArray_creal_T *b_X;
  emxArray_creal_T *r0;
  unsigned short iter_M1;
  emxArray_creal_T *b_Y;
  emxArray_creal_T *r1;

  /*  2D FFT using 1D FFT */
  i0 = Y->size[0] * Y->size[1];
  Y->size[0] = M1;
  Y->size[1] = M2;
  emxEnsureCapacity_creal_T(Y, i0);
  loop_ub = M1 * M2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    Y->data[i0].re = 0.0;
    Y->data[i0].im = 0.0;
  }

  iter_cols = 0;
  emxInit_creal_T(&b_X, 1);
  emxInit_creal_T(&r0, 1);
  while (iter_cols <= X->size[1] - 1) {
    loop_ub = X->size[0];
    i0 = b_X->size[0];
    b_X->size[0] = loop_ub;
    emxEnsureCapacity_creal_T1(b_X, i0);
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_X->data[i0] = X->data[i0 + X->size[0] * iter_cols];
    }

    fft(b_X, M1, r0);
    loop_ub = r0->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      Y->data[i0 + Y->size[0] * iter_cols] = r0->data[i0];
    }

    iter_cols++;
  }

  emxFree_creal_T(&r0);
  emxFree_creal_T(&b_X);
  iter_M1 = 1U;
  emxInit_creal_T1(&b_Y, 2);
  emxInit_creal_T1(&r1, 2);
  while (iter_M1 <= M1) {
    loop_ub = Y->size[1];
    i0 = b_Y->size[0] * b_Y->size[1];
    b_Y->size[0] = 1;
    b_Y->size[1] = loop_ub;
    emxEnsureCapacity_creal_T(b_Y, i0);
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_Y->data[b_Y->size[0] * i0] = Y->data[(iter_M1 + Y->size[0] * i0) - 1];
    }

    b_fft(b_Y, M2, r1);
    loop_ub = r1->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      Y->data[(iter_M1 + Y->size[0] * i0) - 1] = r1->data[r1->size[0] * i0];
    }

    iter_M1++;
  }

  emxFree_creal_T(&r1);
  emxFree_creal_T(&b_Y);
}

/*
 * File trailer for FFT2_.c
 *
 * [EOF]
 */
