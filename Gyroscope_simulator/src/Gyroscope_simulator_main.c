
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8SB2_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include <ILI9413_lib.h>
#include <Gyroscope_simulator_main.h>
#include <stdio.h>
// $[Generated Includes]
// [Generated Includes]$

SI_SBIT(KEY_CTS, SFR_P0, 6);

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------

char KeyClick();

void main(void) {
	uint16_t GYRO=0;       // Used to store character from UART
	int i,BOXSIZE=30,REZIM=0;
	char t2;
	enter_DefaultMode_from_RESET();
	SCON0_TI = 1;
	//SIN_COS=false;
	ILI9341_init();
	Text_color = returnColor24_16(0x00 , 0xff , 0xff);
	TextSize(2);
	TFT_line = 0;
	TFT_char = 0;
	while (1) {
		if(REZIM==0){
			fillScreen(returnColor24_16(0x00 , 0x00 , 0x00));
				for (i=0; i <4;i++){
					fillRect( BOXSIZE*i, 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*i, 315, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*i, 120, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*(i+1), 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
				}
				TFT_line = 6;
				TFT_char = 10;
				lcdPrintString ("Rezistor" );
				TFT_line = 6+BOXSIZE;
				TFT_char = 10;
				lcdPrintString ("SIN_COS" );
				TFT_line = 6+BOXSIZE*2;
				TFT_char = 10;
				lcdPrintString ("FORM FROM MENU" );
				TFT_line = 6+BOXSIZE*3;
				TFT_char = 10;
				lcdPrintString ("+//- BUTHOM" );
				TFT_line = 6+BOXSIZE*4;
				TFT_char = 10;
			t2 = KeyClick();
			if(t2=='1')REZIM =1;
			if(t2=='2')REZIM =2;
			if(t2=='3')REZIM =3;
			if(t2=='4')REZIM =4;
			Delay(100);
		}
		if(REZIM==1){
			SIN_COS=false;
			Delay(100);
		}
		if(REZIM==2){
			lcdPrintString ("SIN_COS");
			TFT_line = 6+BOXSIZE*5;
			TFT_char = 10;
			lcdPrintString ("Press any key for reset");
			SIN_COS=true;
			KeyClick();
			REZIM = 0;
			SIN_COS=false;
			Delay(100);
		}
		if(REZIM==3){
			SIN_COS=false;
			fillScreen(returnColor24_16(0x00 , 0x00 , 0x00));
				for (i=0; i <4;i++){
					fillRect( BOXSIZE*i, 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*i, 315, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*i, 120, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
					fillRect( BOXSIZE*(i+1), 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
				}
				TFT_line = 6;
				TFT_char = 10;
				lcdPrintString ("++--/|/|/|/|" );
				TFT_line = 6+BOXSIZE;
				TFT_char = 10;
				lcdPrintString ("--++/|/|/|/|" );
				TFT_line = 6+BOXSIZE*2;
				TFT_char = 10;
				lcdPrintString ("+-+-/|/|/|/|" );
				TFT_line = 6+BOXSIZE*3;
				TFT_char = 10;
				lcdPrintString ("Reset" );
				TFT_line = 6+BOXSIZE*4;
				TFT_char = 10;
				while(REZIM==3){
					Delay(1000);
					t2 = KeyClick();
					if(t2=='1')REZIM_3 = 1;
					if(t2=='2')REZIM_3 = 2;
					if(t2=='3')REZIM_3 = 3;
					if(t2=='4'){
						REZIM=0;
						REZIM_3=0;
					}
				}
		}
		if(REZIM==4){
			SIN_COS=false;
			fillScreen(returnColor24_16(0x00 , 0x00 , 0x00));
			for (i=0; i <4;i++){
				fillRect( BOXSIZE*i, 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
				fillRect( BOXSIZE*i, 315, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
				fillRect( BOXSIZE*i, 120, BOXSIZE, 5, returnColor24_16(0xff , 0x00 , 0x00));
				fillRect( BOXSIZE*(i+1), 120, 5, 200, returnColor24_16(0xff , 0x00 , 0x00));
			}
			TFT_line = 6;
			TFT_char = 10;
			lcdPrintString ("+++++++++++++" );
			TFT_line = 6+BOXSIZE;
			TFT_char = 10;
			lcdPrintString ("-------------" );
			TFT_line = 6+BOXSIZE*2;
			TFT_char = 10;
			lcdPrintString ("" );
			TFT_line = 6+BOXSIZE*3;
			TFT_char = 10;
			lcdPrintString ("Reset" );
			TFT_line = 6+BOXSIZE*4;
			TFT_char = 10;
			while(REZIM==4){
				Delay(1000);
				t2 = KeyClick();
				if(t2=='1'){
					GYRO = GYRO+1;
					if (GYRO == 4200)GYRO = 0;
					printf ("\nEnter x: %d",GYRO);
					SPI0_GYRO_OUT_DATA_L = GYRO;
					SPI0_GYRO_OUT_DATA_H = GYRO>>8;
					SPI1_GYRO_OUT_DATA_L = GYRO;
					SPI1_GYRO_OUT_DATA_H = GYRO>>8;
				}
				if(t2=='2'){
					GYRO = GYRO-1;
					if (GYRO == -4200)GYRO = 0;
					printf ("\nEnter x: %d",GYRO);
					SPI0_GYRO_OUT_DATA_L = GYRO;
					SPI0_GYRO_OUT_DATA_H = GYRO>>8;
					SPI1_GYRO_OUT_DATA_L = GYRO;
					SPI1_GYRO_OUT_DATA_H = GYRO>>8;
				}
				if(t2=='4')REZIM=0;
			}
		}
	}
}
char KeyClick(){
	Write_8(0x00);
	while (KEY_CTS!=0);
	Write_8(0xEE);
	if (KEY_CTS==0)return '1';
	Write_8(0xDD);
	if (KEY_CTS==0)return '2';
	Write_8(0xBB);
	if (KEY_CTS==0)return '3';
	Write_8(0x77);
	if (KEY_CTS==0)return '4';
	return '0';
}
