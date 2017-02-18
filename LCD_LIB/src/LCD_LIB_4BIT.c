//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8LB1_Register_Enums.h>
#include "LCD_LIB.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library Includes]
// [Library Includes]$
SI_SBIT (LCD_RS, SFR_P1, 5);
SI_SBIT (LCD_E, SFR_P1, 6);
SI_SBIT (LCD_D0, SFR_P1, 3);
SI_SBIT (LCD_D1, SFR_P1, 2);
SI_SBIT (LCD_D2, SFR_P1, 1);
SI_SBIT (LCD_D3, SFR_P1, 0);


int init = 0;

extern void delay(int counts) {
	int i;
	while (counts--) {
		for (i = 0; i < 10; i++);
	}
}
extern void LCD_SEND(DIN) {
	int d, i;
	for (i = 0; i < 4; i++) {
		if (DIN & 0x80)  d = 1;                             // output one data bit"1"
		else d = 0;
		DIN = DIN << 1;
		if (i == 0)
			LCD_D0 = d;
		if (i == 1)
			LCD_D1 = d;
		if (i == 2)
			LCD_D2 = d;
		if (i == 3)
			LCD_D3 = d;
	}
	LCD_E = 1;
	delay(100);
	LCD_E = 0;
	delay(100);
}
extern void LCD_WRITE(DIN) {
	LCD_RS = 1;
	LCD_SEND (DIN);
	LCD_SEND (DIN << 4);
}
extern void LCD_COMAND(DIN) {
	LCD_RS = 0;
	if (!init)	LCD_SEND (DIN);
	LCD_SEND (DIN << 4);
	if (init)	delay(1000);
}
extern void LCD_Init() {
	int i;
	LCD_RS = 0;
	LCD_E = 0;
	init = 1;
	LCD_COMAND(0x03);
	for (i = 0; i < 50; i++)
		delay(1000);
	LCD_COMAND(0x03);
	for (i = 0; i < 10; i++)
		delay(1000);
	LCD_COMAND(0x03);
	for (i = 0; i < 10; i++)
		delay(1000);
	LCD_COMAND(0x02);
	LCD_COMAND(0x02);
	LCD_COMAND(0x00);
	LCD_COMAND(0x00);
	LCD_COMAND(0x0C);
	LCD_COMAND(0x00);
	LCD_COMAND(0x01);
	LCD_COMAND(0x00);
	LCD_COMAND(0x06);
	LCD_COMAND(0x03);
	LCD_COMAND(0x03);
	LCD_COMAND(0x03);
	LCD_COMAND(0x02);
	LCD_COMAND(0x02);
	LCD_COMAND(0x08);
	LCD_COMAND(0x00);
	LCD_COMAND(0x0C);
	LCD_COMAND(0x00);
	LCD_COMAND(0x01);
	LCD_COMAND(0x00);
	LCD_COMAND(0x0C);
	init = 0;
}