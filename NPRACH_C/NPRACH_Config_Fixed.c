/****************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company          : Lekha Wireless Solutions Pvt. Ltd.
* File Name        : NPRACH_Config_Fixed.c
* Function         : NPRACHConfig()
* Description      : Initializes a Structure containing various NPRACH Parameters
                     required for transmission according to 3GPP Release 36.211 v13.4 (2017-04)
* Input parameters : CvArea - Operating Coverage Area
                     PreambleFormat
* Output parameter : stTxParams - Structure containing for NPRACH Transmission parameters
* Return value     : NONE
* Comments         : Files required - freqHops.txt
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"

/** FILE INCLUDES *********************************************************/
UINT8 aui8FreqHopsBuffer[NUM_SC*128] ={
                                  #include "freqHops.txt"
                                  };

/** GLOBAL VARIABLE DEFINITIONS **********************************************/
UINT8 aui8NprachSC[4]            = {12, 24, 36, 48};           // Set of Sub carriers for Random Access
UINT8 aui8NscOffset[7]           = {0, 12, 24, 36, 2, 18, 34}; // Set of available Sub carrier Offsets

void NPRACHConfig(UINT8 ui8CvArea,UINT8 ui8PreambleFormat)
{

  /* Operating SNR (in dB) for different Coverage Areas */

  switch (ui8CvArea)
  {
    case 1:
      stTxParams.ui8NumReps = 2;    //No. of Symbol Group Repetitions in the Transmission
      break;
    case 2:
      stTxParams.ui8NumReps = 8;    //No. of Symbol Group Repetitions in the Transmission
      break;
    case 3:
      stTxParams.ui8NumReps = 32;   //No. of Symbol Group Repetitions in the Transmission
      break;
    default:
      stTxParams.ui8NumReps = 0;
  }

  stTxParams.ui8UADTHCVA1 = 14;
  stTxParams.ui8UADTHCVA2 = 12;
  stTxParams.ui8UADTHCVA3 = 10;

  stTxParams.ui8CvArea    = ui8CvArea;

  stTxParams.ui8NumSymGrpsPerRep  = 4; // No. of Symbol Groups in one repetition
  stTxParams.ui8NumIdenSymsPerGrp = 5; // No. of Identical Symbols in one Symbol Group
  stTxParams.ui8NumUplinkSC       = 48; // No. of Sub carriers for Up link Transmission


  for (ui32Row = 0; ui32Row < 12; ui32Row++)
    {
    for (ui32Col = 0; ui32Col < 128; ui32Col++)
      {
       stTxParams.aui8FreqHops[ui32Row ][ui32Col] = aui8FreqHopsBuffer[ui32Row *128 + ui32Col];
      }
    }

  /* Set of Sub carriers for Random Access */

  for (ui32Iter = 0; ui32Iter < 4; ui32Iter++)
  {
    stTxParams.aui8NprachSC[ui32Iter] = aui8NprachSC[ui32Iter];
  }

  stTxParams.ui8NPRACHSC    = 48;  // Allocated No. of Sub carriers for Random Access

  stTxParams.ui8NPRACHRASC  = 12;  // No. of Sub carriers for Random Access per PRB

  /* Set of available Sub carrier Offsets */

  for (ui32Iter = 0; ui32Iter < 7; ui32Iter++)
  {
    stTxParams.aui8NscOffset[ui32Iter] = aui8NscOffset[ui32Iter];
  }

  stTxParams.ui8NSCOFFSET   = 0; // Chosen Sub carrier Offset

  stTxParams.ui8CellID      = 1; // Cell ID

  stTxParams.ui8PreambleFormat = ui8PreambleFormat; // Preamble Format

  /* FFT Length */

  stTxParams.ui16OFDMN = 512 ;// Fs * Ts * 5 * 8192 / ui8NumIdenSymsPerGrp : Fs = 1.92e6, Ts = 1/(15000*2048)

  /* CP length for each Preamble Format */

  if (stTxParams.ui8PreambleFormat == 0)
    {
    stTxParams.ui16CpLen = stTxParams.ui16OFDMN / 4;
    }
  else if (stTxParams.ui8PreambleFormat == 1)
    {
    stTxParams.ui16CpLen = stTxParams.ui16OFDMN;
    }

  /* FFT Lengths for the 2D FFT */

  stTxParams.ui16FFT2M2 = 256; // Higher FFT Length for Better Precision in RCFO Estimation
  stTxParams.ui16FFT2M1 = stTxParams.ui16CpLen;


  /*
  Max to Mean of Correlation based Threshold for User Activity Detection
  The System is able to achieve False Alarm rate: NOT TESTED and Successful
  Detection rate: 99.14% with the threshold of 15.9 for PRM_0 and 13.1
  for PRM_1 (99.28%)
  */

}

/********************** End of file NPRACH_Config_Fixed.c ***********************/
