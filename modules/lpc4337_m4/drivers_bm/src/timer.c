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
 *
 * All rights reserved.
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

/** \brief Bare Metal driver for RIT timer in the EDU-CIAA board.
 **
 **/

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
#include "timer.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/

#define LPC4337_MAX_FREC 204000000 /* Microcontroller frequency */
#define MAX_SYSCALL_INTERRUPT_PRIORITY 5

/*==================[internal data declaration]==============================*/

typedef struct{
   LPC_TIMER_T *name;
   uint32_t RGU; /* Reset Generator Unit */
   uint32_t IRQn;
} timerStaticData_t;

typedef struct{
   voidFunctionPointer_t timerCompareMatchFunctionPointer[4];
} timerDinamicData_t;

void (*pIsrTimer)();
void (*pIsrTimer0)();

/*==================[internal functions declaration]=========================*/

static void errorOcurred(void);
static void doNothing(void);

/*==================[internal data definition]===============================*/

/*Timers Static Data, given by the uC libraries*/
static const timerStaticData_t timer_sd[4] = {
   { LPC_TIMER0, RGU_TIMER0_RST, TIMER0_IRQn },
   { LPC_TIMER1, RGU_TIMER1_RST, TIMER1_IRQn },
   { LPC_TIMER2, RGU_TIMER2_RST, TIMER2_IRQn },
   { LPC_TIMER3, RGU_TIMER3_RST, TIMER3_IRQn }
};

/*Timers dynamic data. Function pointers and Compare match frequencies, which can vary.
 * This is the default initialization*/
static timerDinamicData_t timer_dd[4] = {
   {{doNothing,errorOcurred,errorOcurred,errorOcurred}},
   {{doNothing,errorOcurred,errorOcurred,errorOcurred}},
   {{doNothing,errorOcurred,errorOcurred,errorOcurred}},
   {{doNothing,errorOcurred,errorOcurred,errorOcurred}}
};

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/* Causes:
 * User forgot to initialize the functions for the compare match interrupt on Timer_init call
 */
static void errorOcurred(void){
   while(1);
}

static void doNothing(void){
}

/*==================[external functions definition]==========================*/
void timerInit(uint32_t time_ms,void *pfunc){

	pIsrTimer=pfunc;
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,time_ms);
	NVIC_EnableIRQ(RITIMER_IRQn);
}

 void RIT_IRQHandler(){
	Chip_RIT_ClearInt(LPC_RITIMER);
	pIsrTimer();
}

 void ISR_Timer0(){
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 0)) {
	 		Chip_TIMER_ClearMatch(LPC_TIMER0, 0);
	 }
	pIsrTimer0();
}

void timer0Init(uint32_t time_us,void *pfunc){
    pIsrTimer0=pfunc;
	Chip_TIMER_Init(LPC_TIMER0);
	//falta convertit time_ms en el match num
	uint32_t FrecuenciaClk = Chip_Clock_GetBaseClocktHz (CLK_BASE_MX); // Leo la vellocidad del micro en khz
	uint32_t MatchCount= time_us*(FrecuenciaClk/1000000);
	
	Chip_TIMER_SetMatch(LPC_TIMER0, 0, MatchCount);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 0);
	Chip_TIMER_Enable(LPC_TIMER0);
	NVIC_EnableIRQ(TIMER0_IRQn);

}

void timerInterval(uint32_t time){

	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,time);
	NVIC_EnableIRQ(RITIMER_IRQn);
	
}

/*
 * @Purpose:   Allows the user to change the compare value nº
 *    'compareMatchNumber' of timer 'timerNumber'.  This is specially useful to
 *    generate square waves if used in the function for the TIMERCOMPAREMATCH0
 *    (because that compare match resets the timer counter), which will be
 *    passed as a parameter when initializing a timer
 * @note:  The selected time (3rd parameter) must be less than
 *    TIMERCOMPAREMATCH0's compareMatchTime_uS for the compare match to make the
 *    interruption
 */
void timer_SetCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber, uint32_t ticks){
	Chip_TIMER_SetMatch(timer_sd[timerNumber].name, compareMatchNumber,ticks);
}

/*
 * @Brief   Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param   uS:   Value in microseconds
 * @return   Equivalent in Ticks for the LPC4337
 * @note   Can be used for the second parameter in the Timer_init
 */
uint32_t timer_microsecondsToTicks(uint32_t uS){
   return (uS*(LPC4337_MAX_FREC/1000000));
}

void timer_Init( uint8_t timerNumber, uint32_t ticks, voidFunctionPointer_t voidFunctionPointer){
   /* Source:
   http://docs.lpcware.com/lpcopen/v1.03/lpc18xx__43xx_2examples_2periph_2periph__blinky_2blinky_8c_source.html */

   /*If timer period = CompareMatch0 Period = 0 => ERROR*/
   if (ticks==0){
      errorOcurred();
   }

   /* Enable timer clock and reset it */
   Chip_TIMER_Init(timer_sd[timerNumber].name);
   Chip_RGU_TriggerReset(timer_sd[timerNumber].RGU);
   while (Chip_RGU_InReset(timer_sd[timerNumber].RGU)) {}
   Chip_TIMER_Reset(timer_sd[timerNumber].name);

   /* Update the defalut function pointer name of the Compare match 0*/
   timer_dd[timerNumber].timerCompareMatchFunctionPointer[TIMERCOMPAREMATCH0] = voidFunctionPointer;

   /* Initialize compare match with the specified ticks (number of counts needed to clear the match counter) */
   Chip_TIMER_MatchEnableInt(timer_sd[timerNumber].name, TIMERCOMPAREMATCH0);
   Chip_TIMER_SetMatch(timer_sd[timerNumber].name, TIMERCOMPAREMATCH0, ticks);

   /* Makes Timer Match 0 period the timer period*/
   Chip_TIMER_ResetOnMatchEnable(timer_sd[timerNumber].name, TIMERCOMPAREMATCH0);

   /*Enable timer*/
   Chip_TIMER_Enable(timer_sd[timerNumber].name);

   /* Enable timer interrupt */
   NVIC_SetPriority(timer_sd[timerNumber].IRQn, MAX_SYSCALL_INTERRUPT_PRIORITY+1);
   NVIC_EnableIRQ(timer_sd[timerNumber].IRQn);
   NVIC_ClearPendingIRQ(timer_sd[timerNumber].IRQn);
}

/*
 * @Brief   Enables a compare match in a timer
 * @param   timerNumber:   Timer number, 0 to 3
 * @param   compareMatchNumber:   Compare match number, 1 to 3
 * @param   ticks:   Number of ticks required to reach the compare match.
 * @param   voidFunctionPointer: function to be executed when the compare match is reached
 * @return   None
 * @note   For the 'ticks' parameter, see function Timer_microsecondsToTicks
 */
void timer_EnableCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber, uint32_t ticks, voidFunctionPointer_t voidFunctionPointer){

   timer_dd[timerNumber].timerCompareMatchFunctionPointer[compareMatchNumber] = voidFunctionPointer;

   Chip_TIMER_MatchEnableInt(timer_sd[timerNumber].name, compareMatchNumber);
   Chip_TIMER_SetMatch(timer_sd[timerNumber].name, compareMatchNumber, ticks);
}

/*
 * @brief   Disables a compare match of a timer
 * @param   timerNumber:   Timer number, 0 to 3
 * @param   compareMatchNumber:   Compare match number, 1 to 3
 * @return   None
 */
void timer_DisableCompareMatch( uint8_t timerNumber, uint8_t compareMatchNumber ){

   timer_dd[timerNumber].timerCompareMatchFunctionPointer[compareMatchNumber] = errorOcurred;

   Chip_TIMER_ClearMatch(timer_sd[timerNumber].name, compareMatchNumber);
   Chip_TIMER_MatchDisableInt(timer_sd[timerNumber].name, compareMatchNumber);
}

/*==================[ISR external functions definition]======================*/
/*
 * @Brief:   Executes the functions passed by parameter in the Timer_init,
 *   at the chosen frequencies
 */
void TIMER0_IRQHandler(void){

   uint8_t compareMatchNumber = 0;

   for( compareMatchNumber = TIMERCOMPAREMATCH0;
        compareMatchNumber <= TIMERCOMPAREMATCH3;
        compareMatchNumber++ ){
      if( Chip_TIMER_MatchPending(LPC_TIMER0, compareMatchNumber) ){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER0].timerCompareMatchFunctionPointer[compareMatchNumber])();
         Chip_TIMER_ClearMatch(LPC_TIMER0, compareMatchNumber);
      }
   }
}

void TIMER1_IRQHandler( void ){

   uint8_t compareMatchNumber = 0;

   for( compareMatchNumber = TIMERCOMPAREMATCH0;
        compareMatchNumber <= TIMERCOMPAREMATCH3;
        compareMatchNumber++ ){
      if( Chip_TIMER_MatchPending(LPC_TIMER1, compareMatchNumber) ){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER1].timerCompareMatchFunctionPointer[compareMatchNumber])();
         Chip_TIMER_ClearMatch(LPC_TIMER1, compareMatchNumber);
      }
   }
}

void TIMER2_IRQHandler( void ){
   uint8_t compareMatchNumber = 0;

   for( compareMatchNumber = TIMERCOMPAREMATCH0;
        compareMatchNumber <= TIMERCOMPAREMATCH3;
        compareMatchNumber++ ){
      if( Chip_TIMER_MatchPending(LPC_TIMER2, compareMatchNumber) ){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER2].timerCompareMatchFunctionPointer[compareMatchNumber])();
         Chip_TIMER_ClearMatch(LPC_TIMER2, compareMatchNumber);
      }
   }
}

/*fixme __attribute__ ((section(".after_vectors")))*/
void TIMER3_IRQHandler( void ){

   uint8_t compareMatchNumber = 0;

   for( compareMatchNumber = TIMERCOMPAREMATCH0;
        compareMatchNumber <= TIMERCOMPAREMATCH3;
        compareMatchNumber++ ){
      if (Chip_TIMER_MatchPending(LPC_TIMER3, compareMatchNumber)){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER3].timerCompareMatchFunctionPointer[compareMatchNumber])();
         Chip_TIMER_ClearMatch(LPC_TIMER3, compareMatchNumber);
      }
   }
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

