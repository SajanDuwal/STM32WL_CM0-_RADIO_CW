/**
 ******************************************************************************
 * @file    startup_cm0_plus.s
 * @brief   STM32WL55xx Cortex-M0+ CPU2 startup file
 *
 *          Standalone bare-metal startup for STM32WL55 Cortex-M0+.
 *
 *          This file provides:
 *            - Initial stack pointer
 *            - Reset handler
 *            - Cortex-M0+ exception vector table
 *            - STM32WL55 external interrupt vector table
 *            - Weak interrupt handlers
 *            - .data initialization
 *            - .bss initialization
 *            - C runtime initialization
 *            - main() entry
 *
 ******************************************************************************
 */

.syntax unified
.cpu cortex-m0plus
.thumb


/* ============================================================================
 * GLOBAL SYMBOLS
 * ============================================================================ */

.global g_pfnVectors
.global Default_Handler


/* ============================================================================
 * RESET HANDLER
 * ============================================================================ */

.section .text.Reset_Handler,"ax",%progbits

.weak Reset_Handler
.type Reset_Handler, %function

Reset_Handler:

    /* ------------------------------------------------------------------------
     * Set initial stack pointer
     * ------------------------------------------------------------------------ */

    ldr     r0, =_estack
    mov     sp, r0


    /* ------------------------------------------------------------------------
     * Initialize system
     * ------------------------------------------------------------------------ */

    bl      SystemInit


    /* ------------------------------------------------------------------------
     * Copy .data section from FLASH to RAM
     *
     * _sidata = FLASH source address
     * _sdata  = RAM start
     * _edata  = RAM end
     * ------------------------------------------------------------------------ */

    ldr     r0, =_sdata
    ldr     r1, =_edata
    ldr     r2, =_sidata

    movs    r3, #0

    b       LoopCopyDataInit


CopyDataInit:

    ldr     r4, [r2, r3]
    str     r4, [r0, r3]

    adds    r3, r3, #4


LoopCopyDataInit:

    adds    r4, r0, r3
    cmp     r4, r1

    bcc     CopyDataInit


    /* ------------------------------------------------------------------------
     * Zero-fill .bss section
     *
     * _sbss = RAM start of .bss
     * _ebss = RAM end of .bss
     * ------------------------------------------------------------------------ */

    ldr     r2, =_sbss
    ldr     r4, =_ebss

    movs    r3, #0

    b       LoopFillZerobss


FillZerobss:

    str     r3, [r2]
    adds    r2, r2, #4


LoopFillZerobss:

    cmp     r2, r4

    bcc     FillZerobss

    /* ------------------------------------------------------------------------
     * Enter application
     * ------------------------------------------------------------------------ */

    bl      main


    /* ------------------------------------------------------------------------
     * main() should never return
     * ------------------------------------------------------------------------ */

LoopForever:

    b       LoopForever


.size Reset_Handler, . - Reset_Handler


/* ============================================================================
 * DEFAULT HANDLER
 * ============================================================================ */

.section .text.Default_Handler,"ax",%progbits

.type Default_Handler, %function
.global Default_Handler

Default_Handler:

Infinite_Loop:

    b       Infinite_Loop

.size Default_Handler, . - Default_Handler


/* ============================================================================
 * VECTOR TABLE
 * ============================================================================ */

.section .isr_vector,"a",%progbits
.align 2

.type g_pfnVectors, %object
.global g_pfnVectors

g_pfnVectors:

    /* ------------------------------------------------------------------------
     * Cortex-M0+ Core Exceptions
     * ------------------------------------------------------------------------ */

    .word   _estack                 /* Initial Stack Pointer */
    .word   Reset_Handler           /* Reset */
    .word   NMI_Handler             /* NMI */
    .word   HardFault_Handler       /* HardFault */

    .word   0                       /* Reserved */
    .word   0                       /* Reserved */
    .word   0                       /* Reserved */
    .word   0                       /* Reserved */
    .word   0                       /* Reserved */
    .word   0                       /* Reserved */
    .word   0                       /* Reserved */

    .word   SVC_Handler             /* SVCall */

    .word   0                       /* Reserved */
    .word   0                       /* Reserved */

    .word   PendSV_Handler          /* PendSV */
    .word   SysTick_Handler         /* SysTick */

    /* ------------------------------------------------------------------------
     * STM32WL55 Cortex-M0+ External Interrupts
     * ------------------------------------------------------------------------ */

    .word   Default_Handler              /* IRQ 0  - TZIC */
    .word   Default_Handler               /* IRQ 1  - PVD/PVM */
    .word   Default_Handler            /* IRQ 2  - RTC/LSECSS */
    .word   Default_Handler       /* IRQ 3  - RCC/FLASH/CPU1 SEV */
    .word   Default_Handler               /* IRQ 4  - EXTI1:0 */
    .word   Default_Handler               /* IRQ 5  - EXTI3:2 */
    .word   Default_Handler              /* IRQ 6  - EXTI15:4 */
    .word   Default_Handler          /* IRQ 7  - ADC/COMP/DAC */
    .word   Default_Handler     /* IRQ 8  - DMA1 CH1-3 */
    .word   Default_Handler   /* IRQ 9  - DMA1 CH4-7 */
    .word   Default_Handler      /* IRQ 10 - DMA2/DMAMUX */
    .word   Default_Handler                 /* IRQ 11 - LPTIM1 */
    .word   Default_Handler                 /* IRQ 12 - LPTIM2 */
    .word   Default_Handler                 /* IRQ 13 - LPTIM3 */
    .word   Default_Handler                   /* IRQ 14 - TIM1 */
    .word   Default_Handler                   /* IRQ 15 - TIM2 */
    .word   Default_Handler                  /* IRQ 16 - TIM16 */
    .word   Default_Handler                  /* IRQ 17 - TIM17 */
    .word   IPCC_C2_RX_C2_TX_IRQHandler      /* IRQ 18 - IPCC */
    .word   Default_Handler                   /* IRQ 19 - HSEM */
    .word   Default_Handler                    /* IRQ 20 - RNG */
    .word   Default_Handler                /* IRQ 21 - AES/PKA */
    .word   Default_Handler                   /* IRQ 22 - I2C1 */
    .word   Default_Handler                   /* IRQ 23 - I2C2 */
    .word   Default_Handler                   /* IRQ 24 - I2C3 */
    .word   Default_Handler                   /* IRQ 25 - SPI1 */
    .word   Default_Handler                   /* IRQ 26 - SPI2 */
    .word   Default_Handler                 /* IRQ 27 - USART1 */
    .word   USART2_IRQHandler                 /* IRQ 28 - USART2 */
    .word   Default_Handler                /* IRQ 29 - LPUART1 */
    .word   SUBGHZSPI_IRQHandler              /* IRQ 30 - SUBGHZSPI */
    .word   SUBGHZ_Radio_IRQHandler           /* IRQ 31 - SUBGHZ Radio */


    /*******************************************************************************
    *
    * Provide weak aliases for each Exception handler to the Default_Handler.
    * As they are weak aliases, any function with the same name will override
    * this definition.
    *
    *******************************************************************************/

    .weak NMI_Handler
    .thumb_set NMI_Handler, Default_Handler

    .weak HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler

    .weak SVC_Handler
    .thumb_set SVC_Handler, Default_Handler

    .weak PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

    .weak IPCC_C2_RX_C2_TX_IRQHandler
    .thumb_set IPCC_C2_RX_C2_TX_IRQHandler, Default_Handler

    .weak SUBGHZSPI_IRQHandler
    .thumb_set SUBGHZSPI_IRQHandler, Default_Handler

    .weak SUBGHZ_Radio_IRQHandler
    .thumb_set SUBGHZ_Radio_IRQHandler, Default_Handler
