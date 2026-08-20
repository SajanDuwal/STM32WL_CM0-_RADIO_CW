#ifndef UART_DEBUG_H
#define UART_DEBUG_H

#include <stdint.h>

void serial2_init(void);

void uart2_putc(char c);

void uart2_puts(const char *s);

void serial2_print(const char *fmt,...);

void serial2_println(const char *fmt,...);

/* Interrupt-driven RX */
int serial2_read_byte(uint8_t *out_byte);

int serial2_rx_available(void);

/* non-blocking polling RX */
int serial2_try_getc(uint8_t *out_byte);

#endif