/* Minimal TIMER_IF implementation (stub) to satisfy linker for cm0plus build.
 * Replace with board-specific implementation for correct timing behavior.
 */

#include "timer_if.h"
#include "stm32_timer.h"
#include "stm32_systime.h"

UTIL_TIMER_Status_t TIMER_IF_Init(void)
{
    return UTIL_TIMER_OK;
}

UTIL_TIMER_Status_t TIMER_IF_StartTimer(uint32_t timeout)
{
    (void)timeout;
    return UTIL_TIMER_OK;
}

UTIL_TIMER_Status_t TIMER_IF_StopTimer(void)
{
    return UTIL_TIMER_OK;
}

uint32_t TIMER_IF_SetTimerContext(void)
{
    return 0;
}

uint32_t TIMER_IF_GetTimerContext(void)
{
    return 0;
}

uint32_t TIMER_IF_GetTimerElapsedTime(void)
{
    return 0;
}

uint32_t TIMER_IF_GetTimerValue(void)
{
    return 0;
}

uint32_t TIMER_IF_GetMinimumTimeout(void)
{
    return 1;
}

void TIMER_IF_DelayMs(uint32_t delay)
{
    /* Very simple busy-wait loop as a placeholder. Not precise. */
    volatile uint32_t i, loops = delay * 1000U;
    for(i = 0; i < loops; ++i) {
        __asm__ volatile ("nop");
    }
}

uint32_t TIMER_IF_Convert_ms2Tick(uint32_t timeMilliSec)
{
    return timeMilliSec;
}

uint32_t TIMER_IF_Convert_Tick2ms(uint32_t tick)
{
    return tick;
}

uint32_t TIMER_IF_GetTime(uint16_t *subSeconds)
{
    if (subSeconds) *subSeconds = 0;
    return 0;
}

void TIMER_IF_BkUp_Write_Seconds(uint32_t Seconds)
{
    (void)Seconds;
}

uint32_t TIMER_IF_BkUp_Read_Seconds(void)
{
    return 0;
}

void TIMER_IF_BkUp_Write_SubSeconds(uint32_t SubSeconds)
{
    (void)SubSeconds;
}

uint32_t TIMER_IF_BkUp_Read_SubSeconds(void)
{
    return 0;
}
