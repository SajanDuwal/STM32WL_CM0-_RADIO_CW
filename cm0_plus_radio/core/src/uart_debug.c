#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "../inc/uart_debug.h"

/*
 * =====================================================================
 * USART2 on PA2 (TX) / PA3 (RX) with AF7
 * =====================================================================
 * Using USART2 standard peripheral with PA2/PA3 pins on AF7.
 * Standard USART baud rate formula: BRR = fck / baud
 * For 48 MHz clock at 115200 baud: BRR = 48000000 / 115200 = 417
 * =====================================================================
 */

#define RCC_AHB2ENR     (*(volatile uint32_t *)0x5800004C)
#define RCC_APB1ENR1    (*(volatile uint32_t *)0x58000058)
#define RCC_APB1RSTR1   (*(volatile uint32_t *)0x58000028)

#define GPIOA_MODER     (*(volatile uint32_t *)0x48000000)
#define GPIOA_OSPEEDR   (*(volatile uint32_t *)0x48000008)
#define GPIOA_PUPDR     (*(volatile uint32_t *)0x4800000C)
#define GPIOA_AFRL      (*(volatile uint32_t *)0x48000020)

#define USART2_BASE     0x40004400UL
#define USART2_CR1      (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_BRR      (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_ISR      (*(volatile uint32_t *)(USART2_BASE + 0x1C))
#define USART2_RDR      (*(volatile uint32_t *)(USART2_BASE + 0x24))
#define USART2_TDR      (*(volatile uint32_t *)(USART2_BASE + 0x28))

#define USART_CR1_UE    (1<<0)
#define USART_CR1_RE    (1<<2)
#define USART_CR1_TE    (1<<3)

#define NVIC_ISER0    (*(volatile uint32_t *)0xE000E100UL)

#define USART_CR1_RXNEIE    (1U << 5)

#define USART_ISR_RXNE  (1<<5)
#define USART_ISR_TXE   (1<<7)

/* Standard USART baud rate divider: BRR = fck / baud.
   48 MHz / 115200 baud = 417 */
#define USART2_BRR_48MHZ_115200   417u

#define UART2_RX_BUFFER_SIZE 128

static volatile uint8_t uart2_rx_buffer[UART2_RX_BUFFER_SIZE];

static volatile uint16_t uart2_rx_head = 0;
static volatile uint16_t uart2_rx_tail = 0;

void serial2_init(void)
{
    /* GPIOA clock */
    RCC_AHB2ENR |= (1<<0);

    /* USART2 clock enable + reset */
    RCC_APB1ENR1 |= (1<<17);

    RCC_APB1RSTR1 |= (1<<17);
    RCC_APB1RSTR1 &= ~(1<<17);

    /* PA2 = USART2 TX, PA3 = USART2 RX, both AF7 */

    GPIOA_MODER &= ~((3<<4) | (3<<6));
    GPIOA_MODER |= (2<<4) | (2<<6);

    /* AF7 */
    GPIOA_AFRL &= ~((0xF<<8) | (0xF<<12));
    GPIOA_AFRL |= (7<<8) | (7<<12);

    GPIOA_OSPEEDR |= (3<<4) | (3<<6);

    /* RX pull-up */
    GPIOA_PUPDR &= ~((3<<4) | (3<<6));
    /* Idle-high pull-up on the RX line so it doesn't float if nothing
       is driving it. */
    GPIOA_PUPDR |= (1<<6);

    USART2_BRR = USART2_BRR_48MHZ_115200;

    /* Enable TX + RX */
    USART2_CR1 = USART_CR1_TE | USART_CR1_RE;

    /*
     * Enable USART2 RXNE interrupt
     * RXNEIE = bit 5
     */

    USART2_CR1 |= USART_CR1_RXNEIE;

    /*
     * USART2 is IRQ 28.
     * IRQ 0-31 are controlled by ISER0.
     */
    NVIC_ISER0 |= (1U << 28);

    /* Finally enable USART */
    USART2_CR1 |= USART_CR1_UE;

    /* Enable global interrupts */
    __asm volatile ("cpsie i");
}

void uart2_putc(char c)
{

    while(!(USART2_ISR & USART_ISR_TXE));

    USART2_TDR=c;
}

void uart2_puts(const char *s)
{
    while(*s)
    {
        if(*s=='\n')
        {
            uart2_putc('\r');
        }
        uart2_putc(*s++);
    }
}

void serial2_print(const char *fmt,...)
{
    char buf[128];

    va_list args;
    va_start(args,fmt);
    vsnprintf(
        buf,
        sizeof(buf),
        fmt,
        args
    );
    va_end(args);

    uart2_puts(buf);
}

void serial2_println(const char *fmt,...)
{
    char buf[128];

    va_list args;
    va_start(args,fmt);
    vsnprintf(
        buf,
        sizeof(buf),
        fmt,
        args
    );
    va_end(args);

    uart2_puts(buf);
    uart2_puts("\r\n");
}

void USART2_IRQHandler(void)
{
    if (USART2_ISR & USART_ISR_RXNE)
    {
        uint8_t rx;
        uint16_t next_head;

        rx = (uint8_t)(USART2_RDR & 0xFF);

        next_head =
            (uart2_rx_head + 1U) % UART2_RX_BUFFER_SIZE;

        if (next_head != uart2_rx_tail)
        {
            uart2_rx_buffer[uart2_rx_head] = rx;

            uart2_rx_head = next_head;
        }
    }
}

int serial2_rx_available(void)
{
    return (uart2_rx_head - uart2_rx_tail +
            UART2_RX_BUFFER_SIZE) % UART2_RX_BUFFER_SIZE;
}

int serial2_read_byte(uint8_t *out_byte)
{
    if (uart2_rx_head == uart2_rx_tail)
    {
        return 0;
    }

    *out_byte = uart2_rx_buffer[uart2_rx_tail];

    uart2_rx_tail =
        (uart2_rx_tail + 1U) % UART2_RX_BUFFER_SIZE;

    return 1;
}

int serial2_try_getc(uint8_t *out_byte)
{
    if (USART2_ISR & USART_ISR_RXNE)
    {
        *out_byte = (uint8_t)(USART2_RDR & 0xFF);
        return 1;
    }

    return 0;
}