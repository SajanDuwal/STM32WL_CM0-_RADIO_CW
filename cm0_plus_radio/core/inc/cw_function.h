/*
 * cw_function.h
 *
 *  Created on: Aug 5, 2026
 *      Author: sajanduwal
 */

#ifndef INC_CW_FUNCTION_H_
#define INC_CW_FUNCTION_H_

#include "main.h"
#include "../../Middlewares/stm32_radio_driver/radio_driver.h"
#include "uart_debug.h"
#include "tim_delay.h"

#define WPM 18
#define MORSE_UNIT (1200 / WPM)   // 60 ms at 20 WPM

void cw_on();

void cw_off();

// ELEMENT DIT //
void DIT();

// ELEMENT DASH //
void DASH();

// ELEMENT GAP -> This is the space between dit/dah within the same letter //
void ELEMENT_GAP();

// CHARACTER GAP //
void CHAR_GAP();

// WORD GAP //
void WORD_GAP();

// CHARACTER //
void CW_A();
void CW_B();
void CW_C();
void CW_D();
void CW_E();
void CW_F();
void CW_G();
void CW_H();
void CW_I();
void CW_J();
void CW_K();
void CW_L();
void CW_M();
void CW_N();
void CW_O();
void CW_P();
void CW_Q();
void CW_R();
void CW_S();
void CW_T();
void CW_U();
void CW_V();
void CW_W();
void CW_X();
void CW_Y();
void CW_Z();
void CW_HYPHEN();

// Numbers morse code
void CW_0();
void CW_1();
void CW_2();
void CW_3();
void CW_4();
void CW_5();
void CW_6();
void CW_7();
void CW_8();
void CW_9();

void CW_SAT_NAME();

void SEND_HEX_BEACON(const uint8_t *buffer, uint8_t length);

#endif /* INC_CW_FUNCTION_H_ */
