/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 11-Nov-2020 12:16:04
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "FFT2_.h"
#include "main.h"
#include "FFT2__terminate.h"
#include "FFT2__emxAPI.h"
#include "FFT2__initialize.h"

/* Function Declarations */
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static unsigned short argInit_uint16_T(void);
static emxArray_creal_T *c_argInit_UnboundedxUnbounded_c(void);
static void main_FFT2_(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : creal_T
 */
static creal_T argInit_creal_T(void)
{
  creal_T result;

  /* Set the value of the complex variable.
     Change this value to the value that the application requires. */
  result.re = argInit_real_T();
  result.im = argInit_real_T();
  return result;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : unsigned short
 */
static unsigned short argInit_uint16_T(void)
{
  return 0U;
}

/*
 * Arguments    : void
 * Return Type  : emxArray_creal_T *
 */
static emxArray_creal_T *c_argInit_UnboundedxUnbounded_c(void)
{
  emxArray_creal_T *result;
  static int iv0[2] = { 2, 2 };

  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_creal_T(2, iv0);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result->data[idx0 + result->size[0] * idx1] = argInit_creal_T();
    }
  }

  return result;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_FFT2_(void)
{
  emxArray_creal_T *Y;
  emxArray_creal_T *X;
  emxInitArray_creal_T(&Y, 2);

  /* Initialize function 'FFT2_' input arguments. */
  /* Initialize function input argument 'X'. */
  X = c_argInit_UnboundedxUnbounded_c();

  /* Call the entry-point 'FFT2_'. */
  FFT2_(X, argInit_uint16_T(), argInit_uint16_T(), Y);
  emxDestroyArray_creal_T(Y);
  emxDestroyArray_creal_T(X);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  FFT2__initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_FFT2_();

  /* Terminate the application.
     You do not need to do this more than one time. */
  FFT2__terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
