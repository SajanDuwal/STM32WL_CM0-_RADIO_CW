#ifndef TIM_DELAY_H
#define TIM_DELAY_H

#include "stm32wlxx_hal.h"

void tim2_init(void);
void delay_ms(uint32_t ms);

#endif /* TIM_DELAY_H */
