#include "stm32wlxx_hal.h"

#include "../../SubGHz_Phy/App/app_subghz_phy.h"

#include "uart_debug.h"
#include "tim_delay.h"
#include "cw_function.h"

/* VARIABLES */
uint8_t serial2_rx;
uint8_t uart2_rx_buffer[128];
int len_serial2_rx;
uint8_t uart2_rx_buffer[128];
uint8_t uart2_rx_buffer_index = 0;

/*
=========================================================
MAIN FUNCTION
=========================================================
*/

int main(void)
{
    /* MCU INITIALIZATION */

    SystemInit();
    HAL_Init();
    MX_SubGHz_Phy_Init();
    tim2_init();
    serial2_init();

    serial2_print("\r\n");
    serial2_println("================================");
    serial2_println(" STM32WL55JC2 CM0+ BARE_METAL ");
    serial2_println("================================");
    serial2_println("1. Send 0xAA for CW @ 18WPM");
    serial2_println("Waiting to receive CMD.....");

    /* MAIN LOOP */

    while (1)
    {
        /* UART2 IRQ RECEIVER INTERFACE */
        len_serial2_rx = serial2_rx_available();
        if (len_serial2_rx > 0)
        {
            serial2_print("Received: %d bytes\r\n", len_serial2_rx);
            while (serial2_read_byte(&serial2_rx))
            {
                serial2_print("%02X ", serial2_rx);
                uart2_rx_buffer[uart2_rx_buffer_index++] = serial2_rx;
            }
            serial2_println("");
        }

        if(uart2_rx_buffer[0] == 0xAA){
            serial2_println("CW transmission Started");
		    delay_ms(5000U);
		    CW_SAT_NAME();

		    delay_ms(5000U);
		    uint8_t BEACON_TYPE_1[5] = { 0xB1, 0x34, 0xAA, 0x5A, 0xFF };
		    SEND_HEX_BEACON(BEACON_TYPE_1, sizeof(BEACON_TYPE_1));

		    delay_ms(5000U);
		    uint8_t BEACON_TYPE_2[5] = { 0xB2, 0x17, 0x00, 0x00, 0x00 };
		    SEND_HEX_BEACON(BEACON_TYPE_2, sizeof(BEACON_TYPE_2));
		    delay_ms(5000U);
        }
        memset(uart2_rx_buffer, 0, sizeof(uart2_rx_buffer));
        uart2_rx_buffer_index = 0;

        // static uint8_t k = 0;
        // uint8_t s[] = {k, 0x11, 0xB1, 0x1C, 0xFF};

        // for (int i = 0; i < sizeof(s); i++)
        // {
        //     serial2_print("%02X ", s[i]);
        // }
        // serial2_println("");
        // k++;    
        // delay_ms(1000U);   // 1sec delay
    }
    return 0;
}