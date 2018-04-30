/* Copyright 2018
 * 
 * Gassmann Dustin
 * dustingassmann@gmail.com
 *
 * FACENA - UNNE - CORRIENTES - ARGENTINA
 * 
 * All rights reserved.
 *
 * Driver to Servo, no sAPI.
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

/*TODO: make a graphic and explanation of the timer ramp and compare match values
 to make everything clear */

#ifndef SERVO_H_
#define SERVO_H_

/*==================[inclusions]=============================================*/

#include "datatypes.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

/*==================[typedef]================================================*/

typedef enum{
   SERVO_ENABLE, SERVO_DISABLE,
   SERVO_ENABLE_OUTPUT, SERVO_DISABLE_OUTPUT
} servoConfig_t;

typedef enum{
   SERVO0, SERVO1, SERVO2, SERVO3, SERVO4, SERVO5, SERVO6, SERVO7, SERVO8
} servoMap_t;
/*==================[external data declaration]==============================*/


/*
 * @Brief: Initializes the servo peripheral
 * @param  uint8_t servoNumber
 * @param  uint8_t config
 * @return bool_t true (1) if config it is ok
 * @IMPORTANT:   this function uses Timer 1, 2 and 3 to generate the servo signals, so
 *   they won't be available to use.
 */
bool_t servoConfig( servoMap_t servoNumber, servoConfig_t config );

/*
 * @brief:   Tells if the servo is currently active, and its position
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @param:   value:   value of the servo, from 0 to 180
 * @return:   position (1 ~ SERVO_TOTALNUMBER), 0 if the element was not found.
 */
uint8_t servoIsAttached( servoMap_t servoNumber );

/*
 * @brief: read the value of the servo
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @return: value of the servo (0 ~ 180).
 *   If an error ocurred, return = EMPTY_POSITION = 255
 */
uint16_t servoRead( servoMap_t servoNumber );

/*
 * @brief: change the value of the servo
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @param:   value:   value of the servo, from 0 to 180
 * @return: True if the value was successfully changed, False if not.
 */
bool_t servoWrite( servoMap_t servoNumber, uint16_t angle );

uint32_t valueToMicroseconds(uint8_t value);

void timer1CompareMatch0func(void);
void timer1CompareMatch1func(void);
void timer1CompareMatch2func(void);
void timer1CompareMatch3func(void);

void timer2CompareMatch0func(void);
void timer2CompareMatch1func(void);
void timer2CompareMatch2func(void);
void timer2CompareMatch3func(void);

void timer3CompareMatch0func(void);
void timer3CompareMatch1func(void);
void timer3CompareMatch2func(void);
void timer3CompareMatch3func(void);

void servoInitTimers( void );
bool_t servoAttach( servoMap_t servoNumber );
bool_t servoDetach( servoMap_t servoNumber );


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* SAPI_SERVO_H_ */
