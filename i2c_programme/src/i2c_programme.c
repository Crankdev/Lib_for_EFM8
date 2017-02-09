/*
 * i2c_programme.c
 *
 *  Created on: 14 черв. 2016
 *      Author: kill
 */


#include <SI_EFM8LB1_Register_Enums.h>
#include "InitDevice.h"
#include "i2c_programme.h"

int SMB_ERRORS = 0;
int DATA_REQUEST[] = 0;
int DATA_SEND[] = 0;

void SMB_START_BIT(void){
	SCL = 1;
	SDA = 1;
	if  (SDA == 0)SMB_ERRORS=1;
	if	(SCL == 0)SMB_ERRORS=1;
	SDA = 0;
	delay();
	SCL = 0;
	delay();
}
void SMB_STOP_BIT(void){
	SDA = 0;
	delay();
	SCL = 1;
	delay();
	SDA = 1;
	delay();
}
void SMB_SEND_BIT(DIN){
	int i;
	for (i=0;i<8;i++){
		if (DIN & 0x80)  SDA = 1;                             // output one data bit"1"
		else SDA = 0;
		DIN = DIN <<1;
		SMB_SCL();
		delay();
	}
	  SDA = 1;
	  SMB_SCL();
	  delay();
	  SDA = 1;
}
uint8_t SMB_READ_BIT(){
	int i,j;
	uint8_t DIN;
	for (i=0;i<8;i++){
		SCL = 1;
		DIN = DIN <<1;
		for (j=0;j<3;j++);
		DIN  |= SDA;
		for (j=0;j<8;j++);
		SCL = 0;
		delay();
	}
	return DIN;
}
void SMB_SCL(){
	SCL = 1;
	delay();
	SCL = 0;
}
void SMB_SCL1(){
	int i;
	SCL = 1;
	for (i=0;i<1;i++);
	SDA = 0;
	for (i=0;i<10;i++);
	SDA = 1;
	SCL = 0;
}
void delay(){
	int i;
	for (i=0;i<12;i++);
}
void SMB_SEND(Adress,DIN){
	   SMB_START_BIT();//START BIT I2C
	   SMB_SEND_BIT(Adress);//ADRESS
	   if (DIN) SMB_SEND_BIT(DIN);//COMMAND
	   SMB_STOP_BIT();//STOP BIT I2C
}
void SMB_REQUEST(Adress, COL){
	 int i;
	SMB_START_BIT();//START BIT I2C
	   SMB_SEND_BIT(Adress | READ); //ADRESS
	   delay(); //wait
	   for(i=0;i < COL; i++){
		   if (i!=0)SMB_SCL1(); // SCL ASK MASTER
		   DATA_REQUEST[i] = SMB_READ_BIT(); // GET FIRS BIT
	   }
	   SMB_SCL(); //SCL
	   SMB_STOP_BIT();//STOP BIT I2C
}
void SMB_SEND_DATA(Adress, COL){
	int i;
	SMB_START_BIT();//START BIT I2C
	SMB_SEND_BIT(Adress);//ADRESS
	 for(i=0;i < COL; i++){
		   SMB_SEND_BIT(DATA_SEND[i]);
	 }
	SMB_STOP_BIT();//STOP BIT I2C
}
