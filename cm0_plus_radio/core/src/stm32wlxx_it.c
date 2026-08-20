/**
 * stm32wlxx_it.c
 *
 * Minimal interrupt handler file for CPU2 (M0+).
 *
 * This project's startup_cm0p.s leaves SysTick_Handler aliased to the weak
 * Default_Handler, so HAL_IncTick() was never being called and
 * HAL_GetTick() stayed at 0 forever.
 *
 * This provides a real SysTick_Handler that overrides the weak default
 * via strong linkage.
 */

#include "stm32wlxx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}