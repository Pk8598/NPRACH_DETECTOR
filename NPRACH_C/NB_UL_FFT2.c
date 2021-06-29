/******************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company           : Lekha Wireless Solutions Pvt. Ltd.
* File Name         : NB_UL_FFT2.c
* Function          : NBULFFt2()
* Description       : Fixed point 2D FFT implementation
* Input parameters  : Input  - Input matrix (Nrows x Ncols)
                      Output - Output matrix where result is stored
                      M1, M2 - FFT size
                      Nrows, Ncols - Input matrix size
* Output parameters : Output - Output matrix where result is stored
* Return value      : NONE
* Comments          : Calls NBIOT_UL_FFT(), MatSlice() functions
******************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NB_UL_FFT.h"
#include "NPRACH_Fixed.h"

/** GLOBAL VARIABLE DEFINITIONS **********************************************/

CPLX16 acplx16FFtIn   [NUMSYMS_PER_REP];   // declared for worst case input length
CPLX16 acplx16FFtOut  [N];                 // declared for worst case FFT size
CPLX16 acplx16TempOut [N*NUMSYMS_PER_REP]; // matrix to store intermediate results
UINT16 ui16IterCols;
UINT16 ui16IterRows;

void NBULFFt2(CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16M1, UINT16 ui16M2, UINT16 ui16Nrows, UINT16 ui16Ncols)
{
  /*
  Taking each columns('Ncols') of length 'Nrows' from input matrix(2D array)
  and taking M1 point DFT to get a vector(1D array) of length 'M1',
  so the temporary output matrix(2D array) will be of size "M1 x Ncols"
  */

  for (ui16IterCols = 0 ; ui16IterCols < ui16Ncols ; ui16IterCols++)
  {
    MatSlice (pcplx16Input, acplx16FFtIn,0, ui16Nrows, ui16IterCols, ui16IterCols+1, ui16Ncols);

    NBIOT_UL_FFT(acplx16FFtIn , acplx16FFtOut, ui16M1,NUM_SC);

    for(ui32Row = 0 ; ui32Row < ui16M1 ; ui32Row++)
    {
     acplx16TempOut[(ui16IterCols)+(ui32Row*ui16Ncols)].real = acplx16FFtOut[ui32Row].real<<3;
     acplx16TempOut[(ui16IterCols)+(ui32Row*ui16Ncols)].imag = acplx16FFtOut[ui32Row].imag<<3;
    }

    memset(acplx16FFtIn,   0,sizeof(CPLX16)*NUMSYMS_PER_REP);
    memset(acplx16FFtOut,  0,sizeof(CPLX16)*N);

  }

  /*
  Taking each rows('Nrows') of length 'Ncols' from matrix(2D array) obtained above
  and taking M2 point DFT to get a vector(1D array) of length 'M2',
  so the output matrix(2D array) will be of size "M1 x M2"
  */

  for (ui16IterRows = 0; ui16IterRows < ui16M1; ui16IterRows++)
  {
    MatSlice (acplx16TempOut, acplx16FFtIn, ui16IterRows, ui16IterRows+1, 0, ui16Ncols, ui16Ncols);

    NBIOT_UL_FFT(acplx16FFtIn , acplx16FFtOut, ui16M2,NUMSYMS_PER_REP);

    for(ui32Col = 0 ; ui32Col < ui16M2 ; ui32Col++)
    {
     pcplx16Output[(ui16IterRows * ui16M2) + ui32Col].real = acplx16FFtOut[ui32Col].real;
     pcplx16Output[(ui16IterRows * ui16M2) + ui32Col].imag = acplx16FFtOut[ui32Col].imag;
    }

    memset(acplx16FFtIn,   0,sizeof(CPLX16)*NUMSYMS_PER_REP);
    memset(acplx16FFtOut,  0,sizeof(CPLX16)*N);
  }

}

/********************** End of file NB_UL_FFT2.c ***********************/
