/* Copyright 2016, 
 * Federico Pinna
 * fpinna@unsl.edu.ar
 * Eduardo Filomena
 * efilomena@bioingenieria.edu.ar
 * Juan Manuel Reta
 * jmrera@bioingenieria.edu.ar
 * Facultad de Ingeniería
 * Universidad Nacional de Entre Ríos
 * Argentina
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef TIMER_H
#define TIMER_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
 ** @{ */
 
/*
 * Initials     Name
 * ---------------------------
 *  FP          Federico Pinna
 *  EF			Eduardo Filomena
 *  JMR			Juan Manuel Reta
 */


/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160807 v0.2 initial version by Eduardo Filomena 
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif
	
/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/

//NOTE: if servo is enable (servoConfig used) the only available timer to use is TIMER0
typedef enum{
   TIMER0, TIMER1, TIMER2, TIMER3
} timerMap_t;

typedef enum{
   TIMERCOMPAREMATCH0, TIMERCOMPAREMATCH1, TIMERCOMPAREMATCH2, TIMERCOMPAREMATCH3
} timerCompareMatch_t;

typedef void (*voidFunctionPointer_t)(void);

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** \brief Initialization function of RIT (repetitive interrupt timer) 
 ** 
 ** \param[in] elapse time between interrupts in miliseconds 
 **
 ** \param[in] adress of ISR (Interrupt Servide Routine)
 **
 ** \return FALSE if an error occurs, in other case returns TRUE
 **/
void timerInit(uint32_t time_ms,void *pfunc);
void timer0Init(uint32_t time_us,void *pfunc);

/*
 * @Brief   Initialize Timer peripheral
 * @param   timerNumber:   Timer number, 0 to 3
 * @param   ticks:   Number of ticks required to finish the cycle.
 * @param   voidFunctionPointer:   function to be executed at the end of the timer cycle
 * @return   nothing
 * @note   For the 'ticks' parameter, see function Timer_microsecondsToTicks
 */
void timer_Init( uint8_t timerNumber, uint32_t ticks, voidFunctionPointer_t voidFunctionPointer);

/*
 * @Brief   Disables timer peripheral
 * @param   timerNumber:   Timer number, 0 to 3
 * @return   nothing
 */
void Timer_DeInit(uint8_t timerNumber);

//Reasignar timepo de Intervalo al Timer
void timerInterval(uint32_t time);

/*
 * @Purpose:   Allows the user to change the compare value n? 'compareMatchNumber' of timer 'timerNumber'.
 *    This is specially useful to generate square waves if used in the function for the TIMERCOMPAREMATCH0 (because
 *    that compare match resets the timer counter), which will be passed as a parameter when initializing a timer
 * @note:  The selected time (3rd parameter) must be less than TIMERCOMPAREMATCH0's compareMatchTime_uS
 *   for the compare match to make the interruption
 */
void timer_SetCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber, uint32_t ticks);

/*
 * @Brief   Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param   uS:   Value in microseconds
 * @return   Equivalent in Ticks for the LPC4337
 * @note   Can be used for the second parameter in the Timer_init
 */
void timer_SetCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber, uint32_t ticks);

/*
 * @Brief   Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param   uS:   Value in microseconds
 * @return   Equivalent in Ticks for the LPC4337
 * @note   Can be used for the second parameter in the Timer_init
 */
uint32_t timer_microsecondsToTicks(uint32_t uS);

/*
 * @Brief   Enables a compare match in a timer
 * @param   timerNumber:   Timer number, 0 to 3
 * @param   compareMatchNumber:   Compare match number, 1 to 3
 * @param   ticks:   Number of ticks required to reach the compare match.
 * @param   voidFunctionPointer: function to be executed when the compare match is reached
 * @return   None
 * @note   For the 'ticks' parameter, see function Timer_microsecondsToTicks
 */
void timer_EnableCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber, uint32_t ticks, voidFunctionPointer_t voidFunctionPointer);

/*
 * @brief   Disables a compare match of a timer
 * @param   timerNumber:   Timer number, 0 to 3
 * @param   compareMatchNumber:   Compare match number, 1 to 3
 * @return   None
 */
void timer_DisableCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber );

/*==================[ISR external functions declaration]=====================*/
/*
 * @Brief:   Executes the functions passed by parameter in the Timer_init,
 *   at the chosen frequencies
 */
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef TIMER_H */	

