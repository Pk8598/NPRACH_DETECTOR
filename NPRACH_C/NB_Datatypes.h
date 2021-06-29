/******************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company      : Lekha Wireless Solutions Pvt. Ltd.
* File Name    : NB_DataTypes.h
* Description  : File contains datatypes provided by the OS Wrapper
* Comments     : NONE
******************************************************************************/

/** FILE GUARDS **************************************************************/
#ifndef __DATA_TYPES_H
#define __DATA_TYPES_H

/** STANDARD INCLUDES ********************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

/** MACRO AND TYPE DEFINITIONS ***********************************************/

typedef enum
{
    RC_SUCCESS,
    RC_PENDING,
    RC_FAILURE,
    RC_DUPLICATE,
    RC_ERROR,
    RC_ERROR_MEM,
    RC_ERROR_NOT_FOUND,
    RC_ERROR_DENIED,
    RC_ERROR_ALLOC,
    RC_ERROR_INPUT,
    RC_ERROR_FULL,
    RC_ERROR_EMPTY
}RC_t;

typedef char CHAR_t;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef signed char INT8;
typedef signed char SINT8;
typedef signed short INT16;
typedef signed short SINT16;
typedef unsigned long long UINT64;
typedef signed long long INT64;
typedef signed long long SINT64;
#ifdef __x86_64__
typedef unsigned int UINT32;
typedef signed int INT32;
//typedef signed int SINT32;
typedef UINT64 POINTER_t;
#else
typedef unsigned long UINT32;
typedef signed long INT32;
//typedef signed long SINT32;
typedef UINT32 POINTER_t;
#endif

typedef unsigned int WORD_t;

typedef unsigned long long Key_t;


typedef float   FLOAT;
typedef double  DOUBLE;
typedef bool BOOL;
typedef bool boolean;

typedef struct CPLXF_t
{
    FLOAT real;
    FLOAT imag;
} CPLXF;

typedef struct CPLXD_t
{
    DOUBLE real;
    DOUBLE imag;
} CPLXD;

typedef struct CPLXI_t
{
    INT16 real;
    INT16 imag;
} CPLXI;

typedef struct _CPLX16
{
    SINT16 real;
    SINT16 imag;
} CPLX16;

typedef struct _CPLX8
{
    SINT8 real;
    SINT8 imag;

} CPLX8;

typedef struct _CPLX32
{
    INT32 real;
    INT32 imag;
} CPLX32;
#if 0
typedef struct _CPLX32
{
    INT32 real;
    INT32 imag;
} CPLXI32;
#endif

typedef struct CPLXI32_t
{
    INT32 real;
    INT32 imag;

} CPLXI32;

typedef struct CPLXI64_t
{
    INT64 real;
    INT64 imag;
} CPLXI64;

typedef struct CPLXIR32_t
{
    INT32 imag;
    INT32 real;
} CPLXIR32;
#if RM_VERSION
typedef struct Radio_config
{
    UINT32 ui32SampleCount;

}RadioConfig_t;
#endif
#endif

/********************** End of header file NBIOT_DataTypes.h ***********************/
