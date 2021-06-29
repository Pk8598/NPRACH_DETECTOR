/*
 * File: fft.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 11-Nov-2020 12:16:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "FFT2_.h"
#include "fft.h"
#include "FFT2__emxutil.h"
#include "fft1.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                unsigned short varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_fft(const emxArray_creal_T *x, unsigned short varargin_1,
           emxArray_creal_T *y)
{
  emxArray_creal_T *r3;
  int b_x[1];
  emxArray_creal_T c_x;
  int i1;
  int loop_ub;
  emxInit_creal_T(&r3, 1);
  b_x[0] = x->size[1];
  c_x = *x;
  c_x.size = (int *)&b_x;
  c_x.numDimensions = 1;
  c_fft(&c_x, varargin_1, r3);
  i1 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_1;
  emxEnsureCapacity_creal_T(y, i1);
  loop_ub = varargin_1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    y->data[i1] = r3->data[i1];
  }

  emxFree_creal_T(&r3);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                unsigned short varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_creal_T *x, unsigned short varargin_1, emxArray_creal_T *
         y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_creal_T *b_y;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  emxInit_creal_T(&b_y, 1);
  if ((x->size[0] == 0) || (varargin_1 == 0)) {
    N2blue = b_y->size[0];
    b_y->size[0] = varargin_1;
    emxEnsureCapacity_creal_T1(b_y, N2blue);
    if (varargin_1 > x->size[0]) {
      nRows = b_y->size[0];
      N2blue = b_y->size[0];
      b_y->size[0] = nRows;
      emxEnsureCapacity_creal_T1(b_y, N2blue);
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        b_y->data[N2blue].re = 0.0;
        b_y->data[N2blue].im = 0.0;
      }
    }

    N2blue = y->size[0];
    y->size[0] = b_y->size[0];
    emxEnsureCapacity_creal_T1(y, N2blue);
    nRows = b_y->size[0];
    for (N2blue = 0; N2blue < nRows; N2blue++) {
      y->data[N2blue] = b_y->data[N2blue];
    }
  } else {
    useRadix2 = ((varargin_1 & (varargin_1 - 1)) == 0);
    get_algo_sizes(varargin_1, useRadix2, &N2blue, &nRows);
    generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      r2br_r2dit_trig(x, varargin_1, costab, sintab, b_y);
      N2blue = y->size[0];
      y->size[0] = b_y->size[0];
      emxEnsureCapacity_creal_T1(y, N2blue);
      nRows = b_y->size[0];
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue] = b_y->data[N2blue];
      }
    } else {
      dobluesteinfft(x, N2blue, varargin_1, costab, sintab, sintabinv, y);
    }
  }

  emxFree_creal_T(&b_y);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
