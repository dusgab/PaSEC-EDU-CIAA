#include "retardos.h"
#include "chip.h"
#include <stdlib.h>
/**
     * @brief Delay in seconds
     * @param timer_num Timer to use
     * @return delayInSeg Time in seconds
     */
  void delaySec(uint8_t timer_num, uint32_t delayInSec)
  {
     delayMs(timer_num,delayInSec*1000);  
  }
/**
     * @brief Delay in milliseconds
     * @param timer_num Timer to use
     * @return delayInMs Time in milliseconds
     */
  void delayMs(uint8_t timer_num, uint32_t delayInMs)
  {
    if ( timer_num == 0 )
    {
          LPC_TIMER0->TCR = 0x02;                /* reset timer */
          LPC_TIMER0->PR  = 0x00;                /* set prescaler to zero */
          LPC_TIMER0->MR[0] = delayInMs * ((SystemCoreClock) / 1000-1);
          LPC_TIMER0->IR  = 0xff;                /* reset all interrrupts */
          LPC_TIMER0->MCR = 0x04;                /* stop timer on match */
          LPC_TIMER0->TCR = 0x01;                /* start timer */

          /* wait until delay time has elapsed */
          while (LPC_TIMER0->TCR & 0x01);
    }
    else if ( timer_num == 1 )
    {
          LPC_TIMER1->TCR = 0x02;                /* reset timer */
          LPC_TIMER1->PR  = 0x00;                /* set prescaler to zero */
          LPC_TIMER1->MR[0] = delayInMs * ((SystemCoreClock) / 1000-1);
          LPC_TIMER1->IR  = 0xff;                /* reset all interrrupts */
          LPC_TIMER1->MCR = 0x04;                /* stop timer on match */
          LPC_TIMER1->TCR = 0x01;                /* start timer */

          /* wait until delay time has elapsed */
          while (LPC_TIMER1->TCR & 0x01);
    }
    return;
  }
 

  /**
   * @brief Delay in microseconds
   * @param timer_num Timer to use
   * @return delayInUs Time in microseconds
   */
  void delayUs(uint8_t timer_num, uint32_t delayInUs)
    {
      if ( timer_num == 0 )
      {
            LPC_TIMER0->TCR = 0x02;                /* reset timer */
            LPC_TIMER0->PR  = 0x00;                /* set prescaler to zero */
            LPC_TIMER0->MR[0] = delayInUs * ((SystemCoreClock) / 1000000-1);
            LPC_TIMER0->IR  = 0xff;                /* reset all interrrupts */
            LPC_TIMER0->MCR = 0x04;                /* stop timer on match */
            LPC_TIMER0->TCR = 0x01;                /* start timer */

            /* wait until delay time has elapsed */
            while (LPC_TIMER0->TCR & 0x01);
      }
      else if ( timer_num == 1 )
      {
            LPC_TIMER1->TCR = 0x02;                /* reset timer */
            LPC_TIMER1->PR  = 0x00;                /* set prescaler to zero */
            LPC_TIMER1->MR[0] = delayInUs * ((SystemCoreClock) / 1000000-1);
            LPC_TIMER1->IR  = 0xff;                /* reset all interrrupts */
            LPC_TIMER1->MCR = 0x04;                /* stop timer on match */
            LPC_TIMER1->TCR = 0x01;                /* start timer */

            /* wait until delay time has elapsed */
            while (LPC_TIMER1->TCR & 0x01);
      }
      return;
    }
