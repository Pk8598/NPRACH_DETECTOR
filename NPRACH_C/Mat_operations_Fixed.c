/****************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : Mat_operations_Fixed.c
* Description : Contains function definitions related to matrix operations
* Comments    : NONE
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"


/**
This function writes (er-sr) x (ec-sc) values into (er-sr) x (ec-sc) dimension  matrix 'out_mat'
taking values from 'mat' starting from row = sr till row = er from the columns
from col = sc till col = ec
**/
void MatSlice (CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16StRow, UINT16 ui16EnRow, UINT16 ui16StCol, UINT16 ui16EnCol, UINT16 ui16Ncols)
{

  for (ui32Row = ui16StRow; ui32Row < ui16EnRow; ui32Row++)
  {
    for (ui32Col = ui16StCol; ui32Col < ui16EnCol; ui32Col++)
    {
      pcplx16Output[(ui32Row - ui16StRow)*(ui16EnCol - ui16StCol) + (ui32Col - ui16StCol)]  = pcplx16Input[ui32Row*ui16Ncols + ui32Col];
    }
  }

}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the maximum value in the array
**/

INT32 FindMax (INT32 *ai32Arr,UINT32 ui32ArrLen)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT32 ui32Len = 0;
  INT32  i32Max  = 0;

  for (ui32Len = 0; ui32Len < ui32ArrLen; ui32Len++)
  {
    if (ai32Arr[ui32Len] > i32Max)
    {
        i32Max = ai32Arr[ui32Len];}
    }

  return i32Max;
}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the mean value of the elements in the array
**/

 INT32 FindMean (INT32 *ai32Arr,UINT32 ui32ArrLen)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT32 ui32Len = 0;
  INT32  i32Mean = 0;
  INT64  i64Sum  = 0;

  for (ui32Len = 0; ui32Len < ui32ArrLen; ui32Len++)
  {
      i64Sum += (INT32)ai32Arr[ui32Len];
  }
  i32Mean = i64Sum /ui32ArrLen ;

  return i32Mean ;

}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the mean value of the selected elements in the array
i.e, elements from index 'sr' till(including) index 'er'
**/

INT16 FindMeanSel (INT32 *ai32Arr,UINT8 ui8Sind,UINT8 ui8Eind)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT8 ui8Ind     = 0;
  INT16 i16MeanSel = 0;
  INT16 i16Sum     = 0;

  for (ui8Ind = ui8Sind; ui8Ind <= ui8Eind; ui8Ind++)
  {
      i16Sum+= ai32Arr[ui8Ind];
  }

  i16MeanSel = i16Sum /(ui8Eind-ui8Sind+1);

  return i16MeanSel;

}


/**
This function takes estimated outputs and actual outputs as input
and writes estimated and actual outputs into the given file
**/

void FwriteResults (Output_t stOut, FLOAT *afTrueValues, UINT8 ui8CvAreaRx, UINT8 ui8PreambleFormat, FILE *pfResults)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT8 ToA_diff    = 0;
  FLOAT RCFO_diff   = 0;
  FLOAT Actual_RCFO = 0;

  fprintf(pfResults,"**********************************************************************************\n");
  fprintf(pfResults,"Coverage area   : %u\nPreamble format : %u\nRCFO scaling    : 2^17\n",ui8CvAreaRx,ui8PreambleFormat);
  fprintf(pfResults,"UAD format      : Indicator (Actual estimated value before thresholding)\n");
  fprintf(pfResults,"RCFO format     : Scaled estimated value (Actual estimated value)\n");
  fprintf(pfResults,"**********************************************************************************\n\n");
  fprintf(pfResults,"----------------------------------------------------------------------------------\n");
  fprintf(pfResults,"UAD\t\tCVA\t ToA\tToA error\tRCFO(x 10^-6)\tRCFO error(x 10^-6)\n");
  fprintf(pfResults,"----------------------------------------------------------------------------------\n");

  for(ui32Iter = 0 ; ui32Iter < NUM_SC ; ui32Iter++)
  {
    ToA_diff    = abs(stOut.ai16ToA[ui32Iter]  - afTrueValues[ui32Iter]);
    Actual_RCFO = (FLOAT)stOut.ai16RCFO[ui32Iter]/RCFO_SCALE;
    RCFO_diff   = Actual_RCFO - afTrueValues[ui32Iter+NUM_SC];


    fprintf(pfResults,"%u(%u)\t%2u\t %3d\t\t%u\t\t%3d (%7.2f)\t\t%6.2f\n",stOut.aui8UAD[ui32Iter],aui8UAD[ui32Iter],
            stOut.aui8CVA[ui32Iter],stOut.ai16ToA[ui32Iter],ToA_diff,stOut.ai16RCFO[ui32Iter],Actual_RCFO*pow(10,6),RCFO_diff*pow(10,6));

  }

}

/********************** End of file Mat_operations_Fixed.c ***********************/
