/*
 * cw_function.c
 *
 *  Created on: Aug 5, 2026
 *      Author: sajanduwal
 */

#include "cw_function.h"

void cw_on() {
	SUBGRF_SetStandby(STDBY_RC);
	SUBGRF_ClearIrqStatus(IRQ_RADIO_ALL);
	SUBGRF_SetPaConfig(0x04, 0x07, 0x00, 0x01);
	SUBGRF_SetTxParams(RFO_HP, 5, RADIO_RAMP_200_US);
	SUBGRF_SetRfFrequency(435500000);
	SUBGRF_SetTxContinuousWave();
}

void cw_off() {
	SUBGRF_SetStandby(STDBY_RC);
	SUBGRF_ClearIrqStatus(IRQ_RADIO_ALL);
}

void DOT() {
	cw_on();
	delay_ms(MORSE_UNIT);
	ELEMENT_GAP();
}

void DASH() {
	cw_on();
	delay_ms(3 * MORSE_UNIT);
	ELEMENT_GAP();
}

void ELEMENT_GAP() {
	cw_off();
	delay_ms(MORSE_UNIT);
}

void CHAR_GAP() {
	cw_off();
	delay_ms(3 * MORSE_UNIT);
}

void WORD_GAP() {
	cw_off();
	delay_ms(7 * MORSE_UNIT);
}

void CW_A() {
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_B() {
	DASH();
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_C() {
	DASH();
	DOT();
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_D() {
	DASH();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_E() {
	DOT();
	CHAR_GAP();
}
void CW_F() {
	DOT();
	DOT();
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_G() {
	DASH();
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_H() {
	DOT();
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_I() {
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_J() {
	DOT();
	DASH();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_K() {
	DASH();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_L() {
	DOT();
	DASH();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_M() {
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_N() {
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_O() {
	DASH();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_P() {
	DOT();
	DASH();
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_Q() {
	DASH();
	DASH();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_R() {
	DOT();
	DASH();
	DOT();
	CHAR_GAP();
}
void CW_S() {
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_T() {
	DASH();
	CHAR_GAP();
}
void CW_U() {
	DOT();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_V() {
	DOT();
	DOT();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_W() {
	DOT();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_X() {
	DASH();
	DOT();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_Y() {
	DASH();
	DOT();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_Z() {
	DASH();
	DASH();
	DOT();
	DOT();
	CHAR_GAP();
}

// Numbers morse code
void CW_0() {
	DASH();
	DASH();
	DASH();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_1() {
	DOT();
	DASH();
	DASH();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_2() {
	DOT();
	DOT();
	DASH();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_3() {
	DOT();
	DOT();
	DOT();
	DASH();
	DASH();
	CHAR_GAP();
}
void CW_4() {
	DOT();
	DOT();
	DOT();
	DOT();
	DASH();
	CHAR_GAP();
}
void CW_5() {
	DOT();
	DOT();
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_6() {
	DASH();
	DOT();
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_7() {
	DASH();
	DASH();
	DOT();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_8() {
	DASH();
	DASH();
	DASH();
	DOT();
	DOT();
	CHAR_GAP();
}
void CW_9() {
	DASH();
	DASH();
	DASH();
	DASH();
	DOT();
	CHAR_GAP();
}

void CW_HYPHEN() {
	DASH();
	DOT();
	DOT();
	DOT();
	DOT();
	DASH();
	CHAR_GAP();
}

void CW_SAT_NAME() {
	CW_9();
	CW_N();
	CW_2();
	CW_S();
	CW_J();
	WORD_GAP();
	CW_S();
	CW_2();
	CW_S();
	CW_HYPHEN();
	CW_2();
}

void CW_HEX(uint8_t CWL) {
	if (CWL == 0x00) {
		CW_0();
	} else if (CWL == 0x01) {
		CW_1();
	} else if (CWL == 0x02) {
		CW_2();
	} else if (CWL == 0x03) {
		CW_3();
	} else if (CWL == 0x04) {
		CW_4();
	} else if (CWL == 0x05) {
		CW_5();
	} else if (CWL == 0x06) {
		CW_6();
	} else if (CWL == 0x07) {
		CW_7();
	} else if (CWL == 0x08) {
		CW_8();
	} else if (CWL == 0x09) {
		CW_9();
	} else if (CWL == 0x0A) {
		CW_A();
	} else if (CWL == 0x0B) {
		CW_B();
	} else if (CWL == 0x0C) {
		CW_C();
	} else if (CWL == 0x0D) {
		CW_D();
	} else if (CWL == 0x0E) {
		CW_E();
	} else if (CWL == 0x0F) {
		CW_F();
	}
}

void CW_LETTER(uint8_t CWL)
{
   //Hexa decimal values
        if(CWL == 0x00||CWL ==0x30) CW_0();
   else if(CWL == 0x01||CWL ==0x31) CW_1();
   else if(CWL == 0x02||CWL ==0x32) CW_2();
   else if(CWL == 0x03||CWL ==0x33) CW_3();
   else if(CWL == 0x04||CWL ==0x34) CW_4();
   else if(CWL == 0x05||CWL ==0x35) CW_5();
   else if(CWL == 0x06||CWL ==0x36) CW_6();
   else if(CWL == 0x07||CWL ==0x37) CW_7();
   else if(CWL == 0x08||CWL ==0x38) CW_8();
   else if(CWL == 0x09||CWL ==0x39) CW_9();
   else if(CWL == 0x0A||CWL ==0x61||CWL ==0x41) CW_A();
   else if(CWL == 0x0B||CWL ==0x62||CWL ==0x42) CW_B();
   else if(CWL == 0x0C||CWL ==0x63||CWL ==0x43) CW_C();
   else if(CWL == 0x0D||CWL ==0x64||CWL ==0x44) CW_D();
   else if(CWL == 0x0E||CWL ==0x65||CWL ==0x45) CW_E();
   else if(CWL == 0x0F||CWL ==0x66||CWL ==0x46) CW_F();
   //-------------------------

   //normal ascii for CW mission
   else if(CWL == 0x67||CWL ==0x47) CW_G();
   else if(CWL == 0x68||CWL ==0x48) CW_H();
   else if(CWL == 0x69||CWL ==0x49) CW_I();
   else if(CWL == 0x6a||CWL ==0x4a) CW_J();
   else if(CWL == 0x6b||CWL ==0x4b) CW_K();
   else if(CWL == 0x6c||CWL ==0x4c) CW_L();
   else if(CWL == 0x6d||CWL ==0x4d) CW_M();
   else if(CWL == 0x6e||CWL ==0x4e) CW_N();
   else if(CWL == 0x6f||CWL ==0x4f) CW_O();
   else if(CWL == 0x70||CWL ==0x50) CW_P();
   else if(CWL == 0x71||CWL ==0x51) CW_Q();
   else if(CWL == 0x72||CWL ==0x52) CW_R();
   else if(CWL == 0x73||CWL ==0x53) CW_S();
   else if(CWL == 0x74||CWL ==0x54) CW_T();
   else if(CWL == 0x75||CWL ==0x55) CW_U();
   else if(CWL == 0x76||CWL ==0x56) CW_V();
   else if(CWL == 0x77||CWL ==0x57) CW_W();
   else if(CWL == 0x78||CWL ==0x58) CW_X();
   else if(CWL == 0x79||CWL ==0x59) CW_Y();
   else if(CWL == 0x7a||CWL ==0x6a) CW_Z();

   else if(CWL == 0xAA) WORD_GAP();
}

void SEND_HEX_BEACON(const uint8_t *buffer, uint8_t length) {

	for (int i = 0; i < length; i++) {
		uint8_t high_byte = (buffer[i] >> 4) & 0x0F;
		uint8_t low_byte = buffer[i] & 0x0F;

		CW_HEX(high_byte);
		CW_HEX(low_byte);
		serial2_println("CW Byte = %X%X", high_byte, low_byte);
		WORD_GAP();
	}

}
