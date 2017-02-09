//=========================================================

//=========================================================

// USER INCLUDES
#include <SI_EFM8UB2_Register_Enums.h>
#include "ILI9413_lib.h"

// USER PROTOTYPES
// USER FUNCTIONS
SI_SBIT(TFTLCD_D1, SFR_P1, 5);
SI_SBIT(TFTLCD_D0, SFR_P1, 4);

SI_SBIT(TFTLCD_D7, SFR_P1, 3);
SI_SBIT(TFTLCD_D6, SFR_P1, 2);
SI_SBIT(TFTLCD_D5, SFR_P1, 1);
SI_SBIT(TFTLCD_D4, SFR_P1, 0);
SI_SBIT(TFTLCD_D3, SFR_P0, 7);
SI_SBIT(TFTLCD_D2, SFR_P0, 6);



SI_SBIT(TFTLCD_RD, SFR_P2, 2);
SI_SBIT(TFTLCD_WR, SFR_P2, 3);
SI_SBIT(TFTLCD_DC, SFR_P2, 4); //TFTLCD_RS
SI_SBIT(TFTLCD_CS, SFR_P2, 5);
SI_SBIT(TFTLCD_RST, SFR_P2, 6);


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


extern void Write_8(DATA) {
	//printf("\n Write:    ");
	if (DATA & 0x80) TFTLCD_D7 = 1;             //  "1"
	else TFTLCD_D7 = 0;
	if (DATA & 0x40) TFTLCD_D6 = 1;             //  "1"
	else TFTLCD_D6 = 0;
	if (DATA & 0x20) TFTLCD_D5 = 1;             //  "1"
	else TFTLCD_D5 = 0;
	if (DATA & 0x10) TFTLCD_D4 = 1;             //  "1"
	else TFTLCD_D4 = 0;
	if (DATA & 0x08) TFTLCD_D3 = 1;             //  "1"
	else TFTLCD_D3 = 0;
	if (DATA & 0x04) TFTLCD_D2 = 1;             //  "1"
	else TFTLCD_D2 = 0;
	if (DATA & 0x02) TFTLCD_D1 = 1;             //  "1"
	else TFTLCD_D1 = 0;
	if (DATA & 0x01) TFTLCD_D0 = 1;             //  "1"
	else TFTLCD_D0 = 0;
	//printf("\n");
}
extern void writecommand(DATA) {
	TFTLCD_CS = 0;
	TFTLCD_DC = 0;
	TFTLCD_WR = 0;
	Write_8 (DATA);
	Delay(5);
	TFTLCD_WR = 1;
	Delay(5);
	TFTLCD_CS = 1;
}

extern void writedata(DATA) {
	TFTLCD_CS = 0;
	TFTLCD_DC = 1;
	TFTLCD_WR = 0;
	Write_8 (DATA);
	Delay(5);
	TFTLCD_WR = 1;
	Delay(5);
	TFTLCD_CS = 1;
}

extern void ILI9341_init(void) {
		TFTLCD_WR = 0;
		TFTLCD_CS = 1;
		TFTLCD_RD = 1;
		// toggle RST low to reset
	//	TFTLCD_RST = 1;
	//	Delay(5);
		TFTLCD_RST = 0;
		Delay(5);
		TFTLCD_RST = 1;
		TFTLCD_CS = 1;
		Delay(150);
		writecommand(0xEF);
		writedata(0x03);
		writedata(0x80);
		writedata(0x02);

		writecommand(0xCF);
		writedata(0x00);
		writedata(0XC1);
		writedata(0X30);

		writecommand(0xED);
		writedata(0x64);
		writedata(0x03);
		writedata(0X12);
		writedata(0X81);

		writecommand(0xE8);
		writedata(0x85);
		writedata(0x00);
		writedata(0x78);

		writecommand(0xCB);
		writedata(0x39);
		writedata(0x2C);
		writedata(0x00);
		writedata(0x34);
		writedata(0x02);

		writecommand(0xF7);
		writedata(0x20);

		writecommand(0xEA);
		writedata(0x00);
		writedata(0x00);

		writecommand(ILI9341_PWCTR1);    //Power control
		writedata(0x23);   //VRH[5:0]

		writecommand(ILI9341_PWCTR2);    //Power control
		writedata(0x10);   //SAP[2:0];BT[3:0]

		writecommand(ILI9341_VMCTR1);    //VCM control
		writedata(0x3e); //¶Ô±È¶Èµ÷½Ú
		writedata(0x28);

		writecommand(ILI9341_VMCTR2);    //VCM control2
		writedata(0x86);  //--

		writecommand(ILI9341_MADCTL);    // Memory Access Control
		writedata(0x48);

		writecommand(ILI9341_PIXFMT);
		writedata(0x55);

		writecommand(ILI9341_FRMCTR1);
		writedata(0x00);
		writedata(0x18);

		writecommand(ILI9341_DFUNCTR);    // Display Function Control
		writedata(0x08);
		writedata(0x82);
		writedata(0x27);

		writecommand(0xF2);    // 3Gamma Function Disable
		writedata(0x00);

		writecommand(ILI9341_GAMMASET);    //Gamma curve selected
		writedata(0x01);

		writecommand(ILI9341_GMCTRP1);    //Set Gamma
		writedata(0x0F);
		writedata(0x31);
		writedata(0x2B);
		writedata(0x0C);
		writedata(0x0E);
		writedata(0x08);
		writedata(0x4E);
		writedata(0xF1);
		writedata(0x37);
		writedata(0x07);
		writedata(0x10);
		writedata(0x03);
		writedata(0x0E);
		writedata(0x09);
		writedata(0x00);

		writecommand(ILI9341_GMCTRN1);    //Set Gamma
		writedata(0x00);
		writedata(0x0E);
		writedata(0x14);
		writedata(0x03);
		writedata(0x11);
		writedata(0x07);
		writedata(0x31);
		writedata(0xC1);
		writedata(0x48);
		writedata(0x08);
		writedata(0x0F);
		writedata(0x0C);
		writedata(0x31);
		writedata(0x36);
		writedata(0x0F);
		writecommand(ILI9341_SLPOUT);    //Exit Sleep
		writecommand(ILI9341_DISPON);    //Display on
		fillScreen(returnColor24_16(0x00, 0x00, 0x00));
		fillScreen(returnColor24_16(0x00, 0x00, 0x00));

}
extern void fillScreen(uint16_t color) {
  fillRect(0, 0,  ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, color);
}

// fill a rectangle
extern void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	 uint8_t  hi,lo;
  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= ILI9341_TFTWIDTH) || (y >= ILI9341_TFTHEIGHT)) return;
  if((x + w - 1) >= ILI9341_TFTWIDTH)  w = ILI9341_TFTWIDTH  - x;
  if((y + h - 1) >= ILI9341_TFTHEIGHT) h = ILI9341_TFTHEIGHT - y;

  setAddrWindow(x, y, x+w-1, y+h-1);


  hi = color >> 8,
  lo = color;

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
    	writedata(hi);
    	writedata(lo);
    }
  }
}
extern void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

  writecommand(ILI9341_CASET); // Column addr set
  writedata(x0 >> 8);
  writedata(x0 & 0xFF);     // XSTART
  writedata(x1 >> 8);
  writedata(x1 & 0xFF);     // XEND

  writecommand(ILI9341_PASET); // Row addr set
  writedata(y0>>8);
  writedata(y0);     // YSTART
  writedata(y1>>8);
  writedata(y1);     // YEND

  writecommand(ILI9341_RAMWR); // write to RAM
}
extern void drawPixel(int16_t x, int16_t y, uint16_t color) {
  if((x < 0) ||(x >= ILI9341_TFTWIDTH) || (y < 0) || (y >= ILI9341_TFTHEIGHT)) return;
  setAddrWindow(x,y,x+1,y+1);
  writedata(color >> 8);
  writedata(color);
}

extern void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	 uint8_t  hi,lo;
  // Rudimentary clipping
  if((x >= ILI9341_TFTWIDTH) || (y >= ILI9341_TFTHEIGHT)) return;

  if((y+h-1) >= ILI9341_TFTHEIGHT)
    h = ILI9341_TFTHEIGHT-y;
  setAddrWindow(x, y, x, y+h-1);

  hi = color >> 8;
  lo = color;

  while (h!=0) {
	  writedata(hi);
	  writedata(lo);
	  h--;
  }
}


extern void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	 uint8_t  hi,lo;
  // Rudimentary clipping
  if((x >= ILI9341_TFTWIDTH) || (y >= ILI9341_TFTHEIGHT)) return;
  if((x+w-1) >= ILI9341_TFTWIDTH)  w = ILI9341_TFTWIDTH-x;
  setAddrWindow(x, y, x+w-1, y);

  hi= color >> 8;
  lo = color;
  while (w--) {
    writedata(hi);
    writedata(lo);
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
		y=320-y;
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
			if (TFT_char > (240 - 5*Text_size)){ TFT_char = 0; TFT_line += (Text_size *10)+5; }
			if (TFT_line > 320 -Text_size*9 ) TFT_line = 0;
		}
		else
		{
			TFT_char += 6*Text_size;
			if (TFT_char > (320 - 5*Text_size)){ TFT_char = 0; TFT_line += (Text_size *10)+5; }
			if (TFT_line > 240 -Text_size*9 ) TFT_line = 0;
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
			if (TFT_line > 320 -Text_size*9 ) TFT_line = 0;
		}
		else {
			TFT_char =0;
			TFT_line += (Text_size *10)+5;
			if (TFT_line > 240 -Text_size*9 ) TFT_line = 0;
		}
	}
}
extern void TextSize( size ){
	if (TFT_char !=0)	printString('\n', Text_color);
	if (Axis == 1){
	//	TFT_char = 0;
		if ( TFT_char!=0)TFT_line += (Text_size *10)+5;
		if (TFT_line > 320 -Text_size*9 ) TFT_line = 0;
		Text_size = size;
	}
	else {
	//	TFT_char = 0;
		if ( TFT_char!=0)TFT_line += (Text_size *10)+5;
		if (TFT_line > 240 -Text_size*9 ) TFT_line = 0;
		Text_size = size;
	}
}

extern void lcdPrintString( uint8_t *c) {
	while (*c) {
		//	 switch()
		//lcd_CharCheck(*c++);
		printString(*c++, Text_color);
	}
}

extern uint16_t returnColor24_16(R , G , B){
	uint16_t color;
	R = R>>3 ;
	G = G>>2 ;
	B = B>>3 ;
	color = B<<11 | G<<5 |R;
	return color;
}
extern void Delay(S) {
  int t;
  for (t=S;t>0;t--);
}
extern void setRotation(int rotation){
	uint16_t t;

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
	  writecommand(ILI9341_MADCTL);
	  writedata(t); // MADCTL
	  // For 9341, init default full-screen address window:
	  setAddrWindow(0, 0, ILI9341_TFTWIDTH - 1, ILI9341_TFTHEIGHT - 1); // CS_IDLE happens here
 }
