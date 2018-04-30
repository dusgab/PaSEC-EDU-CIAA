/* Copyright 2018
 * 
 * Gassmann Dustin
 * dustingassmann@gmail.com
 *
 * FACENA - UNNE - CORRIENTES - ARGENTINA
 * 
 * All rights reserved.
 *
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 *
 */

/* Date: 2018-04-20 */


#ifndef DATATYPES_H_
#define DATATYPES_H_

/*==================[inclusions]=============================================*/

#include "stdint.h"
#include "chip.h"
#include "board.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
/* Functional states */
#ifndef ON
   #define ON     1
#endif
#ifndef OFF
   #define OFF    0
#endif

/* Electrical states */
#ifndef HIGH
   #define HIGH   1
#endif
#ifndef LOW
   #define LOW    0
#endif

/* Logical states */

#ifndef FALSE
   #define FALSE  0
#endif
#ifndef TRUE
   #define TRUE   (!FALSE)
#endif

/*==================[typedef]================================================*/

/* Define Boolean Data Type */
typedef uint8_t bool_t;

/* Define real Data Types (floating point) */
typedef float  real32_t;
//typedef double real64_t; // In LPC4337 float = double (Floating Point single precision, 32 bits)

/* Define Tick Data Type */
typedef uint64_t tick_t;

/*
 * Function Pointer definition
 * --------------------------------------
 * param:  void * - For passing arguments
 * return: bool_t - For Error Reports
 */
typedef bool_t (*sAPI_FuncPtr_t)(void *);

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * Null Function Pointer definition
 * --------------------------------------
 * param:  void * - Not used
 * return: bool_t - Return always true
 */
bool_t sAPI_NullFuncPtr(void *);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_DATATYPES_H_ */
