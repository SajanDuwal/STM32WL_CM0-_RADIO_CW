#include "tim_delay.h"

void tim2_init(void)
{
    /* Enable TIM2 clock */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    /* Reset TIM2 */
    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM2RST;
    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM2RST;

    /*
     * APB1 timer clock = 48 MHz
     *
     * PSC = 47
     *
     * Timer frequency:
     *
     * 48,000,000 / (47 + 1)
     * = 1,000,000 Hz
     *
     * Therefore:
     * 1 timer tick = 1 us
     */

    TIM2->PSC = 47U;

    /*
     * TIM2 is a 32-bit timer.
     *
     * Maximum ARR makes it free-running:
     *
     * 0 -> 0xFFFFFFFF -> 0 -> ...
     *
     * At 1 MHz this takes about 71.6 minutes
     * to overflow.
     */
    TIM2->ARR = 0xFFFFFFFFU;

    /* Start counting from zero */
    TIM2->CNT = 0U;

    /*
     * Generate update event.
     * This loads PSC/ARR into the timer.
     */
    TIM2->EGR = TIM_EGR_UG;

    /* Start TIM2 */
    TIM2->CR1 |= TIM_CR1_CEN;
}


void delay_ms(uint32_t ms)
{
    /*
     * TIM2 runs at 1 MHz:
     *
     * 1 tick = 1 us
     *
     * Therefore:
     * milliseconds * 1000 = microseconds
     */
    uint32_t target = ms * 1000U;

    uint32_t start = TIM2->CNT;

    /*
     * Unsigned subtraction automatically handles
     * the 32-bit counter wrapping from:
     *
     * 0xFFFFFFFF -> 0
     */
    while ((uint32_t)(TIM2->CNT - start) < target)
    {
        /* Wait */
    }
}