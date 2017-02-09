/*
 * i2c_programme.h
 *
 *  Created on: 14 черв. 2016
 *      Author: kill
 */

#ifndef I2C_PROGRAMME_H_
#define I2C_PROGRAMME_H_

#define  WRITE                    0x00 // SMBus WRITE command
#define  READ                     0x01 // SMBus READ command

// Device addresses (7 bits, LSB is a don't care)
#define  SLAVE_ADDR               0x80 // Device address for slave target

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SI_SBIT (SDA, SFR_P1, 2);              // SMBus on P1.2
SI_SBIT (SCL, SFR_P1, 3);               // and P1.3

extern int SMB_ERRORS;
extern int DATA_REQUEST[];
extern int DATA_SEND[];


void SMB_START_BIT(void);
void SMB_STOP_BIT(void);
void SMB_SEND_BIT(DIN);
void SMB_SEND(Adress,DIN);
uint8_t SMB_READ_BIT();
void SMB_SCL();
void SMB_SCL1();
void SMB_REQUEST(Adress, COL);
void SMB_SEND_DATA(Adress, COL);
void delay();


#endif /* I2C_PROGRAMME_H_ */
