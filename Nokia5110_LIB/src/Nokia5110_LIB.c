//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "Nokia5110_LIB.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library Includes]
// [Library Includes]$
int LCD_line = 0;
int LCD_char_col = 0;

extern void lcdWrite(unsigned char dc, unsigned char value) {
	DC = dc;
	SPI_CS_1 = 0;
	Write_8(value);
	SPI_CS_1 = 1;
}

extern void lcdPrintChar(unsigned char c) {
	int j;
	LCD_char_col++;
	if (LCD_size_y <= LCD_char_col)
		LCD_line++;
	for (j = 0; j < 5; j++) {
		lcdWrite(LCD_D, ASCII[c - 0x20][j]);
	}
	lcdWrite(LCD_D, 0x00);
}
extern void lcd_CharCheck(unsigned char c) {
	if (c >= 20)
		lcdPrintChar(c);
	if (c == '\f')
		lcdClear();
	if (c == '\n') {
		lcdClearLine(LCD_line++);
	}
}
extern void lcdClear() {
	unsigned int i;
	lcdLocate(0, 0);
	for (i = 0; i < 84 * 6; i++)
		lcdWrite(LCD_D, 0);
	lcdLocate(0, 0);
}
extern void lcdClearLine(y) {
	unsigned int i;
	lcdLocate(0, y - 1);
	for (i = 0; i < 84; i++)
		lcdWrite(LCD_D, 0);
	lcdLocate(0, y - 1);
}
extern void DISPLAY_Init() {
	//GND_LCD = 0;
//	Vdd_LCD = 1;
	//LIGHT_LCD = 1;
	SPI_CS_1 = 0;
	RST = 0;

	Delay(10);
	RST = 1;
	RST = 0;

	Delay(10);
	RST = 1;
	SPI_CS_1 = 1;
	SPI_CS_1 = 0;
	lcdWrite(LCD_C, 0x21); //Tell LCD extended commands follow
	lcdWrite(LCD_C, 0xB0); //Set LCD Vop (Contrast)
	lcdWrite(LCD_C, 0x04); //Set Temp coefficent
	lcdWrite(LCD_C, 0x14); //LCD bias mode 1:48 (try 0x13)
	//We must send 0x20 before modifying the display control mode
	lcdWrite(LCD_C, 0x20);
	lcdWrite(LCD_C, 0x0C); //Set display control, normal mode.
	lcdClear();
	lcdLocate(0, 0);
	// SPI_MISO = 1;
	SPI_MOSI = 1;
	SPI_CS_1 = 1;
}
extern void lcdPrintString(char *c) {
	while (*c) {
		//	 switch()
		lcd_CharCheck(*c++);
	}
}
extern void lcdLocate(unsigned char x, unsigned char y) {
	lcdWrite(LCD_C, 64 | y);
	lcdWrite(LCD_C, 128 | x);
}