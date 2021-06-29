/****************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : main.c
* Description : Main function which calls the supporting functions
                NPRACHConfig() and NPRACHDetector() and finally stores the
                result in a file
* Comments    : Calls NPRACHConfig(), NPRACHDetector() and FwriteResults()
                functions
                Change ui8CvAreaRx and/or ui8PreambleFormat for different
                configurations
                Files required - Preamble format 0 -> True_values0_xx.txt
                                 Preamble format 1 -> True_values1_xx.txt
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"

/** FILE INCLUDES *********************************************************/

FLOAT afTrueValues [2*NUM_SC] ={
                                #include "Sample_Test_Data\\PRM_0\\True_values0_1.txt"
                               }; // To test for other file True_values0_xx.txt change xx (1 - 100)

/** GLOBAL VARIABLE DEFINITIONS **********************************************/

UINT8  ui8CvAreaRx       = 3;  // 3 or 2 or 1
UINT8  ui8PreambleFormat = 0;  // 0 or 1
FILE   *pfResults;
char   achfname[20];

int main()
{
  /** System Configurations **/

  NPRACHConfig(ui8CvAreaRx, ui8PreambleFormat);

  printf("************************** NPRACH Configurations *****************************\n");
  printf("Coverage area         : %u  || Preamble format : %u\n",ui8CvAreaRx,ui8PreambleFormat);
  printf("Number of repetitions : %u || FFT size : M1 = %u, M2 =%u || CP length : %u\n",stTxParams.ui8NumReps,stTxParams.ui16FFT2M1,stTxParams.ui16FFT2M2,stTxParams.ui16CpLen);
  printf("******************************************************************************\n");

  /** NPRACH Receiver **/

  printf("\nRunning........\n");
  NPRACHDetector();

  /** Writing results obtained i.e, ToA,RCFO,CVA and UAD into separate files to compare it with the Matlab results **/

  sprintf(achfname, "Sample_Test_Results\\PRM_0\\Results_PRM%u.txt",ui8PreambleFormat);
  pfResults = fopen(achfname,"w+");

  FwriteResults(stOut, afTrueValues, ui8CvAreaRx, ui8PreambleFormat, pfResults);

  fclose(pfResults);

  printf("\n************************** SUCCESS *****************************\n");
  printf("\Detection finished, Obtained results stored in '%s'\n",achfname);
  printf("****************************************************************\n");

}

/********************** End of file main.c ***********************/
