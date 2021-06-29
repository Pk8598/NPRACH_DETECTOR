/*
 * File: fft1.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 11-Nov-2020 12:16:04
 */

#ifndef FFT1_H
#define FFT1_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "FFT2__types.h"

/* Function Declarations */
extern void c_fft(const emxArray_creal_T *x, int n, emxArray_creal_T *y);
extern void dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
extern void generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
extern void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows);
extern void r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);

#endif

/*
 * File trailer for fft1.h
 *
 * [EOF]
 */
