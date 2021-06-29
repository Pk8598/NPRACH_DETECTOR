/******************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company      : Lekha Wireless Solutions Pvt. Ltd.
* File Name    : NPRACH_Fixed.h
* Description  : File contains Macros,type and functions definitions
* Comments     : NONE
******************************************************************************/

/** FILE GUARDS **************************************************************/
#ifndef NPRACH_FIXED_H
#define NPRACH_FIXED_H

/** PROJECT INCLUDES *********************************************************/
#include "NB_Datatypes.h"

/** MACRO AND TYPE DEFINITIONS ***********************************************/

#define CVA                     3
#define PRM                     0
#define NUM_SC                  12
#define LEN_1                   393216    // length of UETx for preamble format = 1
#define LEN_0                   344064    // length of UETx for preamble format = 0
#define NUM_SYM_GRPS_3          128       // for CVA = 3 (32*4)
#define NUM_SYM_GRPS_2          32        // for CVA = 2 (8*4)
#define NUM_SYM_GRPS_1          8         // for CVA = 1 (2*4)
#define NUM_SYMS_PER_SYMGRP     5
#define NUMSYMS_PER_REP         20     // 4 * NUM_SYMS_PER_SYMGRP
#define NUMSYMS_3               640    // for CVA = 3 (128*5)
#define NUMSYMS_2               160    // for CVA = 2 (32*5)
#define NUMSYMS_1               40     // for CVA = 1 (8*5)
#define N                       512    // FFT size
#define RCFO_SCALE              131072 // 2^17(N * M2 = 512 * 256)

#if CVA == 3
   #define NUM_SYM_GRPS  NUM_SYM_GRPS_3
   #define NUMSYMS       NUMSYMS_3

#elif CVA == 2
   #define NUM_SYM_GRPS  NUM_SYM_GRPS_2
   #define NUMSYMS       NUMSYMS_2

#else
   #define NUM_SYM_GRPS  NUM_SYM_GRPS_1
   #define NUMSYMS       NUMSYMS_1

#endif

typedef struct TxParams
{
 UINT8  ui8NumReps;
 UINT8  ui8CvArea;
 UINT8  ui8UADTHCVA1;
 UINT8  ui8UADTHCVA2;
 UINT8  ui8UADTHCVA3;
 UINT8  ui8NumSymGrpsPerRep;
 UINT8  ui8NumIdenSymsPerGrp;
 UINT8  ui8NumUplinkSC;
 UINT8  aui8NprachSC[4];
 UINT8  ui8NPRACHSC;
 UINT8  ui8NPRACHRASC;
 UINT8  aui8NscOffset[7];
 UINT8  ui8NSCOFFSET;
 UINT8  ui8CellID;
 UINT8  ui8PreambleFormat;
 UINT16 ui16OFDMN;
 UINT16 ui16CpLen;
 UINT16 ui16FFT2M1;
 UINT16 ui16FFT2M2;
 UINT8  aui8FreqHops[12][128];
}TxParams_t;

typedef struct Output
{
 INT16   ai16ToA [12];
 UINT8   aui8UAD [12];
 UINT8   aui8CVA [12];
 INT16   ai16RCFO[12];
}Output_t;

/** FUNCTION PROTOTYPES ***********************************************/

void NPRACHConfig(UINT8 ui8CvArea,UINT8 ui8PreambleFormat);

void NPRACHDetector();

Output_t NPRACHDetectorPrm0(UINT8 ui8Flag);

void MatSlice (CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16StRow, UINT16 ui16EnRow, UINT16 ui16StCol, UINT16 ui16EnCol, UINT16 ui16Ncols);

INT32 FindMax (INT32 *ai32Arr,UINT32 ui32ArrLen);

INT32 FindMean (INT32 *ai32Arr,UINT32 ui32ArrLen);

INT16 FindMeanSel (INT32 *ai32Arr,UINT8 ui8Sind,UINT8 ui8Eind);

void FwriteResults (Output_t stOut, FLOAT *afTrueValues, UINT8 ui8CvAreaRx, UINT8 ui8PreambleFormat, FILE *pfResults);

/** GENERAL VARIABLES ***********************************************/

UINT32 ui32Iter;
UINT32 ui32Row;
UINT32 ui32Col;
UINT8  aui8UAD [12];
TxParams_t stTxParams;
Output_t   stOut;

#endif

/********************** End of header file NPRACH_Fixed.h ***********************/
