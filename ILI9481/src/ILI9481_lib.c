//=========================================================

//=========================================================

// USER INCLUDES
#include <SI_EFM8UB2_Register_Enums.h>
#include "ILI9481_lib.h"

// USER PROTOTYPES
// USER FUNCTIONS

//SI_SBIT(TFTLCD_RD, SFR_P0, 0);
SI_SBIT(TFTLCD_RS, SFR_P0, 2); //TFTLCD_RS
SI_SBIT(TFTLCD_WR, SFR_P0, 3);
SI_SBIT(TFTLCD_CS, SFR_P0, 6);
SI_SBIT(TFTLCD_RST, SFR_P0, 7);

int TFT_line=0, TFT_char=0,Text_size=0, Axis=0;
uint16_t Text_color=0;
extern unsigned char code ASCII[][5] = {
	//1 First 32 characters (0x00-0x19) are ignored. These are
	// non-displayable, control characters.
	{	0x00, 0x00, 0x00, 0x00, 0x00} // 0x20      0
	, {	0x00, 0x00, 0x5f, 0x00, 0x00} // 0x21 !		1
	, {	0x00, 0x07, 0x00, 0x07, 0x00} // 0x22 "		2
	, {	0x14, 0x7f, 0x14, 0x7f, 0x14} // 0x23 #		3
	, {	0x24, 0x2a, 0x7f, 0x2a, 0x12} // 0x24 $		4
	, {	0x23, 0x13, 0x08, 0x64, 0x62} // 0x25 %		5
	, {	0x36, 0x49, 0x55, 0x22, 0x50} // 0x26 &		6
	, {	0x00, 0x05, 0x03, 0x00, 0x00} // 0x27 '		7
	, {	0x00, 0x1c, 0x22, 0x41, 0x00} // 0x28 (		8
	, {	0x00, 0x41, 0x22, 0x1c, 0x00} // 0x29 )		9
	, {	0x14, 0x08, 0x3e, 0x08, 0x14} // 0x2a *	`	10
	, {	0x08, 0x08, 0x3e, 0x08, 0x08} // 0x2b +		11
	, {	0x00, 0x50, 0x30, 0x00, 0x00} // 0x2c ,		12
	, {	0x08, 0x08, 0x08, 0x08, 0x08} // 0x2d -		13
	, {	0x00, 0x60, 0x60, 0x00, 0x00} // 0x2e .		14
	, {	0x20, 0x10, 0x08, 0x04, 0x02} // 0x2f /		15
	, {	0x3e, 0x51, 0x49, 0x45, 0x3e} // 0x30 0		16
	, {	0x00, 0x42, 0x7f, 0x40, 0x00} // 0x31 1		17
	, {	0x42, 0x61, 0x51, 0x49, 0x46} // 0x32 2		18
	, {	0x21, 0x41, 0x45, 0x4b, 0x31} // 0x33 3		19
	, {	0x18, 0x14, 0x12, 0x7f, 0x10} // 0x34 4		20
	, {	0x27, 0x45, 0x45, 0x45, 0x39} // 0x35 5		21
	, {	0x3c, 0x4a, 0x49, 0x49, 0x30} // 0x36 6		22
	, {	0x01, 0x71, 0x09, 0x05, 0x03} // 0x37 7		23
	, {	0x36, 0x49, 0x49, 0x49, 0x36} // 0x38 8		24
	, {	0x06, 0x49, 0x49, 0x29, 0x1e} // 0x39 9		25
	, {	0x00, 0x36, 0x36, 0x00, 0x00} // 0x3a :		26
	, {	0x00, 0x56, 0x36, 0x00, 0x00} // 0x3b ;		27
	, {	0x08, 0x14, 0x22, 0x41, 0x00} // 0x3c <		28
	, {	0x14, 0x14, 0x14, 0x14, 0x14} // 0x3d =		29
	, {	0x00, 0x41, 0x22, 0x14, 0x08} // 0x3e >		30
	, {	0x02, 0x01, 0x51, 0x09, 0x06} // 0x3f ?		31
	, {	0x32, 0x49, 0x79, 0x41, 0x3e} // 0x40 @		32
	, {	0x7e, 0x11, 0x11, 0x11, 0x7e} // 0x41 A		33
	, {	0x7f, 0x49, 0x49, 0x49, 0x36} // 0x42 B		34
	, {	0x3e, 0x41, 0x41, 0x41, 0x22} // 0x43 C		35
	, {	0x7f, 0x41, 0x41, 0x22, 0x1c} // 0x44 D		36
	, {	0x7f, 0x49, 0x49, 0x49, 0x41} // 0x45 E		37
	, {	0x7f, 0x09, 0x09, 0x09, 0x01} // 0x46 F		38
	, {	0x3e, 0x41, 0x49, 0x49, 0x7a} // 0x47 G		39
	, {	0x7f, 0x08, 0x08, 0x08, 0x7f} // 0x48 H		40
	, {	0x00, 0x41, 0x7f, 0x41, 0x00} // 0x49 I		41
	, {	0x20, 0x40, 0x41, 0x3f, 0x01} // 0x4a J		42
	, {	0x7f, 0x08, 0x14, 0x22, 0x41} // 0x4b K		43
	, {	0x7f, 0x40, 0x40, 0x40, 0x40} // 0x4c L		44
	, {	0x7f, 0x02, 0x0c, 0x02, 0x7f} // 0x4d M		45
	, {	0x7f, 0x04, 0x08, 0x10, 0x7f} // 0x4e N		46
	, {	0x3e, 0x41, 0x41, 0x41, 0x3e} // 0x4f O		47
	, {	0x7f, 0x09, 0x09, 0x09, 0x06} // 0x50 P		48
	, {	0x3e, 0x41, 0x51, 0x21, 0x5e} // 0x51 Q		49
	, {	0x7f, 0x09, 0x19, 0x29, 0x46} // 0x52 R		50
	, {	0x46, 0x49, 0x49, 0x49, 0x31} // 0x53 S		51
	, {	0x01, 0x01, 0x7f, 0x01, 0x01} // 0x54 T		52
	, {	0x3f, 0x40, 0x40, 0x40, 0x3f} // 0x55 U		53
	, {	0x1f, 0x20, 0x40, 0x20, 0x1f} // 0x56 V		54
	, {	0x3f, 0x40, 0x38, 0x40, 0x3f} // 0x57 W		55
	, {	0x63, 0x14, 0x08, 0x14, 0x63} // 0x58 X		56
	, {	0x07, 0x08, 0x70, 0x08, 0x07} // 0x59 Y		57
	, {	0x61, 0x51, 0x49, 0x45, 0x43} // 0x5a Z		58
	, {	0x00, 0x7f, 0x41, 0x41, 0x00} // 0x5b [		59
	, {	0x02, 0x04, 0x08, 0x10, 0x20} // 0x5c \		60
	, {	0x00, 0x41, 0x41, 0x7f, 0x00} // 0x5d ]		61
	, {	0x04, 0x02, 0x01, 0x02, 0x04} // 0x5e ^		63
	, {	0x40, 0x40, 0x40, 0x40, 0x40} // 0x5f _		64
	, {	0x00, 0x01, 0x02, 0x04, 0x00} // 0x60 `		65
	, {	0x20, 0x54, 0x54, 0x54, 0x78} // 0x61 a		66
	, {	0x7f, 0x48, 0x44, 0x44, 0x38} // 0x62 b		67
	, {	0x38, 0x44, 0x44, 0x44, 0x20} // 0x63 c		68
	, {	0x38, 0x44, 0x44, 0x48, 0x7f} // 0x64 d		69
	, {	0x38, 0x54, 0x54, 0x54, 0x18} // 0x65 e		70
	, {	0x08, 0x7e, 0x09, 0x01, 0x02} // 0x66 f		71
	, {	0x0c, 0x52, 0x52, 0x52, 0x3e} // 0x67 g		72
	, {	0x7f, 0x08, 0x04, 0x04, 0x78} // 0x68 h		73
	, {	0x00, 0x44, 0x7d, 0x40, 0x00} // 0x69 i		74
	, {	0x20, 0x40, 0x44, 0x3d, 0x00} // 0x6a j		75
	, {	0x7f, 0x10, 0x28, 0x44, 0x00} // 0x6b k		76
	, {	0x00, 0x41, 0x7f, 0x40, 0x00} // 0x6c l		77
	, {	0x7c, 0x04, 0x18, 0x04, 0x78} // 0x6d m		78
	, {	0x7c, 0x08, 0x04, 0x04, 0x78} // 0x6e n		79
	, {	0x38, 0x44, 0x44, 0x44, 0x38} // 0x6f o		80
	, {	0x7c, 0x14, 0x14, 0x14, 0x08} // 0x70 p		81
	, {	0x08, 0x14, 0x14, 0x18, 0x7c} // 0x71 q		82
	, {	0x7c, 0x08, 0x04, 0x04, 0x08} // 0x72 r		83
	, {	0x48, 0x54, 0x54, 0x54, 0x20} // 0x73 s		84
	, {	0x04, 0x3f, 0x44, 0x40, 0x20} // 0x74 t		85
	, {	0x3c, 0x40, 0x40, 0x20, 0x7c} // 0x75 u		86
	, {	0x1c, 0x20, 0x40, 0x20, 0x1c} // 0x76 v		87
	, {	0x3c, 0x40, 0x30, 0x40, 0x3c} // 0x77 w		88
	, {	0x44, 0x28, 0x10, 0x28, 0x44} // 0x78 x		89
	, {	0x0c, 0x50, 0x50, 0x50, 0x3c} // 0x79 y		90
	, {	0x44, 0x64, 0x54, 0x4c, 0x44} // 0x7a z		91
	, {	0x00, 0x08, 0x36, 0x41, 0x00} // 0x7b {		92
	, {	0x00, 0x00, 0x7f, 0x00, 0x00} // 0x7c |		93
	, {	0x00, 0x41, 0x36, 0x08, 0x00} // 0x7d }		94
	, {	0x10, 0x08, 0x08, 0x10, 0x08} // 0x7e ~		95
	, {	0x78, 0x46, 0x41, 0x46, 0x78} // 0x7f DEL	97
};


extern void Write_8(DATA)
{
	P2 = DATA;
}

extern void LCD_Writ_Bus(ch,cl)
{
	P2 = cl;
	P1 = ch;
}

extern void LCD_Write_COM(VL)
{
	TFTLCD_RS = 0;
	Write_8 (VL);
	pulse();
}

extern void LCD_Write_DATA(VH,VL)
{
	TFTLCD_RS = 1;
	LCD_Writ_Bus(VH,VL);
	pulse();
}
extern void writedata(DATA)
{
	TFTLCD_RS = 1;
	Write_8 (DATA);
	pulse();
}

extern void ILI9481_init()
{
		TFTLCD_WR = 1;
		TFTLCD_CS = 0;

		TFTLCD_RST = 0;
		Delay(15);
		TFTLCD_RST = 1;
		Delay(15);

		Delay(150);
		LCD_Write_COM(0x11);
		Delay(20);
		LCD_Write_COM(0xD0);
		writedata(0x07);
		writedata(0x42);
		writedata(0x18);

		LCD_Write_COM(0xD1);
		writedata(0x00);
		writedata(0x07);
		writedata(0x10);

		LCD_Write_COM(0xD2);
		writedata(0x01);
		writedata(0x02);

		LCD_Write_COM(0xC0);
		writedata(0x10);
		writedata(0x3B);
		writedata(0x00);
		writedata(0x02);
		writedata(0x11);

		LCD_Write_COM(0xC5);
		writedata(0x03);

		LCD_Write_COM(0xC8);
		writedata(0x00);
		writedata(0x32);
		writedata(0x36);
		writedata(0x45);
		writedata(0x06);
		writedata(0x16);
		writedata(0x37);
		writedata(0x75);
		writedata(0x77);
		writedata(0x54);
		writedata(0x0C);
		writedata(0x00);

		LCD_Write_COM(0x36);
		writedata(0x0A);


		LCD_Write_COM(0x3A);
		writedata(0x55);

		LCD_Write_COM(0x2A);
		writedata(0x00);
		writedata(0x00);
		writedata(0x01);
		writedata(0x3F);

		LCD_Write_COM(0x2B);
		writedata(0x00);
		writedata(0x00);
		writedata(0x01);
		writedata(0xE0);
		Delay(120);
		lcdOn();
		fillScreen(0x00);
	//	fillScreen(returnColor24_16(0x00, 0x00, 0x00));

}
extern void fillScreen(uint16_t color) {
  fillRect(0, 0,  TFTWIDTH, TFTHEIGHT, color);
}
// fill a rectangle
extern void fillRect(int x1, int y1, int x2, int y2, uint16_t color)
{
	int x3,y3;
	int i;
	if (x1>x2)
	{
		x3 = x1;
		x1 = x2;
		x2 = x3;
	}
	if (y1>y2)
	{
		y3 = y1;
		y1 = y2;
		y2 = y3;
	}
  // rudimentary clipping (drawChar w/big text requires this)
  setAddrWindow(x1, y1, x2, y2);
  TFTLCD_RS = 1;
  LCD_Writ_Bus(color >> 8,color);
  i=(x2-x1)*(y2-y1);
  while(i!=0) {
	  i--;
	  pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();pulse();
  }
}

extern void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	LCD_Write_COM(0x2a);
	writedata(x0>>8);
	writedata(x0);
	writedata(x1>>8);
	writedata(x1);
	LCD_Write_COM(0x2b);
	writedata(y0>>8);
	writedata(y0);
	writedata(y1>>8);
	writedata(y1);
	LCD_Write_COM(0x2c);
}
extern void drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if((x < 0) ||(x >= TFTWIDTH) || (y < 0) || (y >= TFTHEIGHT)) return;
  setAddrWindow(x,y,x+1,y+1);
  LCD_Write_DATA(color >> 8,color);
}

extern void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  // Rudimentary clipping
  if((x >= TFTWIDTH) || (y >= TFTHEIGHT)) return;
  if((y+h-1) >= TFTHEIGHT) h = TFTHEIGHT-y;
  setAddrWindow(x, y, x, y+h-1);

  LCD_Write_DATA(color >> 8,color);
  while (h--) {
	  pulse();
  }
}


extern void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  // Rudimentary clipping
  if((x >= TFTWIDTH) || (y >= TFTHEIGHT)) return;
  if((x+w-1) >= TFTWIDTH)  w = TFTHEIGHT-x;
  setAddrWindow(x, y, x+w-1, y);

  LCD_Write_DATA(color >> 8,color);
  while (w--) {
	  pulse();
  }
}
extern void printChar (_char ,int16_t x, int16_t y, uint16_t color){
	int i,T;
	i=0;
	if (Axis == 1){
		if (_char & 0x01) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x02) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x04) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x08) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x10) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x20) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x40) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
		i +=Text_size+1;
		if (_char & 0x80) for (T = Text_size; T >=0 ;T--)drawPixel(y, x+i+T, color);
	}
	else
	{
	//	x=320-x;
		y=TFTHEIGHT-y;
		if (_char & 0x01) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x02) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x04) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x08) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x10) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x20) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x40) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
		i +=Text_size+1;
		if (_char & 0x80) for (T = Text_size; T >=0 ;T--)drawPixel(x+i+T, y, color);
	}
}

extern void printString(_char , uint16_t color){
	int j,T;
	if (_char >= 20){
		for (j = 0; j < 5; j++) {
			for (T = Text_size; T > 0 ;T--)	printChar( ASCII[_char - 0x20][j] , TFT_line,  TFT_char+(j*Text_size)+T, color);
		}
		if (Axis == 1){
			TFT_char += 6*Text_size;
			if (TFT_char > (TFTWIDTH - 5*Text_size)){ TFT_char = 0; TFT_line += (Text_size *10)+5; }
			if (TFT_line > TFTHEIGHT -Text_size*9 ) TFT_line = 0;
		}
		else
		{
			TFT_char += 6*Text_size;
			if (TFT_char > (TFTHEIGHT - 5*Text_size)){ TFT_char = 0; TFT_line += (Text_size *10)+5; }
			if (TFT_line > TFTWIDTH -Text_size*9 ) TFT_line = 0;
		}
	}
	if (_char == '\f'){
		fillScreen(returnColor24_16(0x00 , 0x00 , 0x00)); //lcdClear();
		TFT_char = 0;
		TFT_line = 0;
	}
	if (_char == '\n') {
		if (Axis == 1){
			TFT_char =0;
			TFT_line += (Text_size *10)+5;
			if (TFT_line > TFTHEIGHT -Text_size*9 ) TFT_line = 0;
		}
		else {
			TFT_char =0;
			TFT_line += (Text_size *10)+5;
			if (TFT_line > TFTWIDTH -Text_size*9 ) TFT_line = 0;
		}
	}
}
extern void TextSize( size ){
	if (TFT_char !=0)	printString('\n', Text_color);
	if (Axis == 1){
	//	TFT_char = 0;
		if ( TFT_char!=0)TFT_line += (Text_size *10)+5;
		if (TFT_line > TFTHEIGHT -Text_size*9 ) TFT_line = 0;
		Text_size = size;
	}
	else {
	//	TFT_char = 0;
		if ( TFT_char!=0)TFT_line += (Text_size *10)+5;
		if (TFT_line > TFTWIDTH -Text_size*9 ) TFT_line = 0;
		Text_size = size;
	}
}

extern void lcdPrintString( uint8_t *c) {
	while (*c) {
		printString(*c++, Text_color);
	}
}

extern uint16_t returnColor24_16(R , G , B){
	uint16_t color;
	R = R>>3 ;
	G = G>>2 ;
	B = B>>3 ;
	color = R<<11 | G<<5 |B;
	return color;
}
extern void Delay(S) {
  int t;
  for (t=S;t>0;t--);
}

extern void setRotation(int rotation){
/*	uint16_t t;
	  switch (rotation) {
	  case 2:
		t = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
		break;
	  case 3:
		t = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
		break;
	 case 0:
	   t = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
	   break;
	  case 1:
		t = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
		break;
	 }
	  LCD_Write_COM(ILI9341_MADCTL);
	  writedata(t); // MADCTL
	  // For 9341, init default full-screen address window:
	  setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1); // CS_IDLE happens here
 */
 }
extern void lcdOff()
{
	LCD_Write_COM(0x28);
}

extern void lcdOn()
{
	LCD_Write_COM(0x29);
}
extern void pulse()
{
	//Delay(5);
	TFTLCD_WR = 0;
	TFTLCD_WR = 1;
}
//
extern void drawRect(int x1, int y1, int x2, int y2, uint16_t color)
{
	int x3,y3;
	if (x1>x2)
	{
		x3 = x1;
		x1 = x2;
		x2 = x3;
	}
	if (y1>y2)
	{
		y3 = y1;
		y1 = y2;
		y2 = y3;
	}

	drawFastHLine(x1, y1, x2-x1,color);
	drawFastHLine(x1, y2, x2-x1,color);
	drawFastVLine(x1, y1, y2-y1,color);
	drawFastVLine(x2, y1, y2-y1,color);
}


extern void drawRoundRect(int x1, int y1, int x2, int y2, uint16_t color)
{
	int x3,y3;
	if (x1>x2)
	{
		x3 = x1;
		x1 = x2;
		x2 = x3;
	}
	if (y1>y2)
	{
		y3 = y1;
		y1 = y2;
		y2 = y3;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawFastVLine(x1, y1+2, y2-y1-4,color);
		drawFastVLine(x2, y1+2, y2-y1-4,color);
		drawPixel(x1+1,y1+1,color);
		drawPixel(x2-1,y1+1,color);
		drawPixel(x1+1,y2-1,color);
		drawPixel(x2-1,y2-1,color);
		drawFastHLine(x1+2, y1, x2-x1-4,color);
		drawFastHLine(x1+2, y2, x2-x1-4,color);

	}
}
extern void fillRoundRect(int x1, int y1, int x2, int y2, uint16_t color)
{
	int x3,y3,i;
	if (x1>x2)
	{
		x3 = x1;
		x1 = x2;
		x2 = x3;
	}
	if (y1>y2)
	{
		y3 = y1;
		y1 = y2;
		y2 = y3;
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawFastHLine(x1+2, y1+i, x2-x1-4,color);
				drawFastHLine(x1+2, y2-i, x2-x1-4,color);
				break;
			case 1:
				drawFastHLine(x1+1, y1+i, x2-x1-2,color);
				drawFastHLine(x1+1, y2-i, x2-x1-2,color);
				break;
			default:
				drawFastHLine(x1, y1+i, x2-x1,color);
				drawFastHLine(x1, y2-i, x2-x1,color);
			}
		}
	}
}

extern void drawCircle(int x, int y, int radius, uint16_t color)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;

	setAddrWindow(x, y + radius, x, y + radius);
	LCD_Write_DATA(color>>8,color);
	setAddrWindow(x, y - radius, x, y - radius);
	LCD_Write_DATA(color>>8,color);
	setAddrWindow(x + radius, y, x + radius, y);
	LCD_Write_DATA(color>>8,color);
	setAddrWindow(x - radius, y, x - radius, y);
	LCD_Write_DATA(color>>8,color);

	while(x1 < y1)
	{
		if(f >= 0)
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		setAddrWindow(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(color>>8,color);
		setAddrWindow(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(color>>8,color);
	}
	//clrXY();
}

extern void fillCircle(int x, int y, int radius, uint16_t color)
{
	int x1,y1;
	for( y1=-radius; y1<=0; y1++)
		for( x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius)
			{
				drawFastHLine(x+x1, y+y1, 2*(-x1),color);
				drawFastHLine(x+x1, y-y1, 2*(-x1),color);
			}
}
/*
extern void _fast_fill_16(int ch, int cl, long pix)
{
	long blocks;
	int i;
	P1 = ch;
	P2 = cl;

	blocks = pix/16;
	for (i=0; i<blocks; i++)
	{
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
		pulse();
	}
	if ((pix % 16) != 0)
		for (i=0; i<(pix % 16)+1; i++)
		{
			pulse();
		}
}
*/