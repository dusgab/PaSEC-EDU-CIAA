#ifndef DRV_DEVICES_H_
#define DRV_DEVICES_H_


#include "lpc_types.h"
  /**
   * @brief
   * @note
   */
  void delaySec(uint8_t timer_num, uint32_t delayInMs); 
  void delayMs(uint8_t timer_num, uint32_t delayInMs);
  void delayUs(uint8_t timer_num, uint32_t delayInUs);

  /**
   * @}
   */

#endif /* DRV_DEVICES_H_ */