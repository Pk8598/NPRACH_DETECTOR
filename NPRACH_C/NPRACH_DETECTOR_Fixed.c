/****************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical withstOut the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company           : Lekha Wireless Solutions Pvt. Ltd.
* File Name         : NPRACH_DETECTOR_Fixed.c
* Function          : NPRACHDetector()
* Description       : Estimates Time-of-Arrival and Residual Carrier Frequency Offset using
                      NPRACHDetectorPrm0() function
* Input parameters  : NONE
* Output parameters : Structure containing following elements:
                      ToA  - Time-of-Arrival Estimates
                      RCFO - Residual CFO Estimates
                      UAD  - User Activity Detection
                      CVA  - Estimated Coverage Area for each UE
* Return value      : NONE
* Comments          : Calls NPRACHDetectorPrm0() function
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"

void NPRACHDetector()
{
  if (stTxParams.ui8PreambleFormat == 0)
    {
      stOut = NPRACHDetectorPrm0(0);

      for (ui32Iter = 0; ui32Iter < NUM_SC; ui32Iter++)
      {
          aui8UAD [ui32Iter] = stOut.aui8UAD[ui32Iter];

          if ( (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA3 && stOut.aui8CVA[ui32Iter] == 3 ) ||
               (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA2 && stOut.aui8CVA[ui32Iter] == 2 ) ||
               (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA1 && stOut.aui8CVA[ui32Iter] == 1 ))
            {
               stOut.aui8UAD[ui32Iter] = 1;
            }
          else
            {
               stOut.aui8UAD[ui32Iter] = 0;
            }
      }
    }

  else if (stTxParams.ui8PreambleFormat == 1)
    {
      /* Phase roll over happens as the FFT Lengths increase and thus for
      detecting Timing offsets over CpLen / 2 with better accuracy and
      precision, we propose two hypothesis - 1. We perform NPRACH
      Detection on the Received Signal and 2. We perform NPRACH
      Detection on a -(CpLen / 2) shifted Received Signal and take
      whichever gives better Correlation
      */

      /* This above method is only needed for Long CP (Preamble Format 1) */

      Output_t stOut1     = NPRACHDetectorPrm0(0);

      Output_t stOut2     = NPRACHDetectorPrm0(1);

      for (ui32Iter = 0; ui32Iter < NUM_SC; ui32Iter++)
        {

          if (stOut1.aui8UAD[ui32Iter] >= stOut2.aui8UAD[ui32Iter])
            {
              stOut.ai16ToA[ui32Iter]   = stOut1.ai16ToA[ui32Iter];
              stOut.ai16RCFO[ui32Iter]  = stOut1.ai16RCFO[ui32Iter];
              stOut.aui8UAD[ui32Iter]   = stOut1.aui8UAD[ui32Iter];
              stOut.aui8CVA[ui32Iter]   = stOut1.aui8CVA[ui32Iter];
            }
          else
            {
              stOut.ai16ToA[ui32Iter]  = (((UINT16)(stOut2.ai16ToA[ui32Iter] + stTxParams.ui16CpLen / 2 - 1))% stTxParams.ui16CpLen) + 1;
              stOut.ai16RCFO[ui32Iter]  = stOut2.ai16RCFO[ui32Iter];
              stOut.aui8UAD[ui32Iter]   = stOut2.aui8UAD[ui32Iter];
              stOut.aui8CVA[ui32Iter]   = stOut2.aui8CVA[ui32Iter];
            }

          aui8UAD [ui32Iter] = stOut.aui8UAD[ui32Iter];

          if ( (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA3 && stOut.aui8CVA[ui32Iter] == 3 ) ||
               (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA2 && stOut.aui8CVA[ui32Iter] == 2 ) ||
               (stOut.aui8UAD[ui32Iter] >= stTxParams.ui8UADTHCVA1 && stOut.aui8CVA[ui32Iter] == 1 ))
            {
              stOut.aui8UAD[ui32Iter] = 1;
            }
          else
            {
              stOut.aui8UAD[ui32Iter] = 0;
            }
        }
    }

}

/********************** End of file NPRACH_DETECTOR_Fixed.c ***********************/
