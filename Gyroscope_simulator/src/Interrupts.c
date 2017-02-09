


#include <SI_EFM8SB2_Register_Enums.h>
#include <Gyroscope_simulator_main.h>
#include <ILI9413_lib.h>
//SI_SBIT (LED1, SFR_P1, 1);             // Green LED
#define LED_ON   0
#define LED_OFF  1

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define SYSCLK                24500000 // Internal oscillator frequency in Hz

#define SPI_CLOCK               500000 // Maximum SPI clock
                                       // The SPI clock is a maximum of 1 MHz
                                       // when this example is used with
                                       // the SPI0_Slave code example.
#define  ERROR_OCCURRED           0x40 // Indicator for the Slave to tell the
                                       // Master an error o

#define  TEMP_OUT           0x02

#define  GYRO_OUT2          0x04

#define  GYRO_OUT           0x06

#define  SERIAL_NUM         0x3A


uint8_t SPI_Data = 0x00;
uint8_t SPI0_TEMP_OUT_DATA_1   = 0X00;
uint8_t SPI0_TEMP_OUT_DATA_2   = 0X00;
uint8_t SPI0_GYRO_OUT2_DATA_1  = 0X00;
uint8_t SPI0_GYRO_OUT2_DATA_2  = 0X00;
uint8_t SPI0_GYRO_OUT_DATA_L   = 0X00;
uint8_t SPI0_GYRO_OUT_DATA_H   = 0X00;
uint8_t SPI0_SERIAL_NUM_DATA   = 0X00;
uint8_t SPI1_TEMP_OUT_DATA_1   = 0X00;
uint8_t SPI1_TEMP_OUT_DATA_2   = 0X00;
uint8_t SPI1_GYRO_OUT2_DATA_1  = 0X00;
uint8_t SPI1_GYRO_OUT2_DATA_2  = 0X00;
uint8_t SPI1_GYRO_OUT_DATA_L   = 0X00;
uint8_t SPI1_GYRO_OUT_DATA_H   = 0X00;
uint8_t SPI1_SERIAL_NUM_DATA   = 0X00;

bool SIN_COS = true;
int SIN=0,COS=64,REZIM_3;
int16_t GYRO_1=0,GYRO_0=0;
// A full cycle, 16-bit, unsigned sine wave lookup table
const uint16_t code SINE_TABLE[256] =
{
		   0x0000, 0x0324, 0x0647, 0x096a, 0x0c8b, 0x0fab, 0x12c8, 0x15e2,
		   0x18f8, 0x1c0b, 0x1f19, 0x2223, 0x2528, 0x2826, 0x2b1f, 0x2e11,
		   0x30fb, 0x33de, 0x36ba, 0x398c, 0x3c56, 0x3f17, 0x41ce, 0x447a,
		   0x471c, 0x49b4, 0x4c3f, 0x4ebf, 0x5133, 0x539b, 0x55f5, 0x5842,
		   0x5a82, 0x5cb4, 0x5ed7, 0x60ec, 0x62f2, 0x64e8, 0x66cf, 0x68a6,
		   0x6a6d, 0x6c24, 0x6dca, 0x6f5f, 0x70e2, 0x7255, 0x73b5, 0x7504,
		   0x7641, 0x776c, 0x7884, 0x798a, 0x7a7d, 0x7b5d, 0x7c29, 0x7ce3,
		   0x7d8a, 0x7e1d, 0x7e9d, 0x7f09, 0x7f62, 0x7fa7, 0x7fd8, 0x7ff6,
		   0x7fff, 0x7ff6, 0x7fd8, 0x7fa7, 0x7f62, 0x7f09, 0x7e9d, 0x7e1d,
		   0x7d8a, 0x7ce3, 0x7c29, 0x7b5d, 0x7a7d, 0x798a, 0x7884, 0x776c,
		   0x7641, 0x7504, 0x73b5, 0x7255, 0x70e2, 0x6f5f, 0x6dca, 0x6c24,
		   0x6a6d, 0x68a6, 0x66cf, 0x64e8, 0x62f2, 0x60ec, 0x5ed7, 0x5cb4,
		   0x5a82, 0x5842, 0x55f5, 0x539b, 0x5133, 0x4ebf, 0x4c3f, 0x49b4,
		   0x471c, 0x447a, 0x41ce, 0x3f17, 0x3c56, 0x398c, 0x36ba, 0x33de,
		   0x30fb, 0x2e11, 0x2b1f, 0x2826, 0x2528, 0x2223, 0x1f19, 0x1c0b,
		   0x18f8, 0x15e2, 0x12c8, 0x0fab, 0x0c8b, 0x096a, 0x0647, 0x0324,

		   0x0000, 0xfcdc, 0xf9b9, 0xf696, 0xf375, 0xf055, 0xed38, 0xea1e,
		   0xe708, 0xe3f5, 0xe0e7, 0xdddd, 0xdad8, 0xd7da, 0xd4e1, 0xd1ef,
		   0xcf05, 0xcc22, 0xc946, 0xc674, 0xc3aa, 0xc0e9, 0xbe32, 0xbb86,
		   0xb8e4, 0xb64c, 0xb3c1, 0xb141, 0xaecd, 0xac65, 0xaa0b, 0xa7be,
		   0xa57e, 0xa34c, 0xa129, 0x9f14, 0x9d0e, 0x9b18, 0x9931, 0x975a,
		   0x9593, 0x93dc, 0x9236, 0x90a1, 0x8f1e, 0x8dab, 0x8c4b, 0x8afc,
		   0x89bf, 0x8894, 0x877c, 0x8676, 0x8583, 0x84a3, 0x83d7, 0x831d,
		   0x8276, 0x81e3, 0x8163, 0x80f7, 0x809e, 0x8059, 0x8028, 0x800a,
		   0x8000, 0x800a, 0x8028, 0x8059, 0x809e, 0x80f7, 0x8163, 0x81e3,
		   0x8276, 0x831d, 0x83d7, 0x84a3, 0x8583, 0x8676, 0x877c, 0x8894,
		   0x89bf, 0x8afc, 0x8c4b, 0x8dab, 0x8f1e, 0x90a1, 0x9236, 0x93dc,
		   0x9593, 0x975a, 0x9931, 0x9b18, 0x9d0e, 0x9f14, 0xa129, 0xa34c,
		   0xa57e, 0xa7be, 0xaa0b, 0xac65, 0xaecd, 0xb141, 0xb3c1, 0xb64c,
		   0xb8e4, 0xbb86, 0xbe32, 0xc0e9, 0xc3aa, 0xc674, 0xc946, 0xcc22,
		   0xcf05, 0xd1ef, 0xd4e1, 0xd7da, 0xdad8, 0xdddd, 0xe0e7, 0xe3f5,
		   0xe708, 0xea1e, 0xed38, 0xf055, 0xf375, 0xf696, 0xf9b9, 0xfcdc,
		/*// A full cycle, 12-bit, unsigned sine wave lookup table
   0x7FF, 0x831, 0x863, 0x895, 0x8C7, 0x8F9, 0x92B, 0x95C,
   0x98E, 0x9BF, 0x9F0, 0xA20, 0xA51, 0xA81, 0xAB0, 0xADF,
   0xB0E, 0xB3C, 0xB6A, 0xB97, 0xBC3, 0xBEF, 0xC1B, 0xC46,
   0xC70, 0xC99, 0xCC2, 0xCEA, 0xD11, 0xD38, 0xD5D, 0xD82,
   0xDA6, 0xDC9, 0xDEB, 0xE0D, 0xE2D, 0xE4C, 0xE6B, 0xE88,
   0xEA5, 0xEC0, 0xEDA, 0xEF4, 0xF0C, 0xF23, 0xF39, 0xF4E,
   0xF62, 0xF74, 0xF86, 0xF96, 0xFA5, 0xFB3, 0xFC0, 0xFCC,
   0xFD6, 0xFDF, 0xFE7, 0xFEE, 0xFF4, 0xFF8, 0xFFB, 0xFFD,
   0xFFE, 0xFFD, 0xFFB, 0xFF8, 0xFF4, 0xFEE, 0xFE7, 0xFDF,
   0xFD6, 0xFCC, 0xFC0, 0xFB3, 0xFA5, 0xF96, 0xF86, 0xF74,
   0xF62, 0xF4E, 0xF39, 0xF23, 0xF0C, 0xEF4, 0xEDA, 0xEC0,
   0xEA5, 0xE88, 0xE6B, 0xE4C, 0xE2D, 0xE0D, 0xDEB, 0xDC9,
   0xDA6, 0xD82, 0xD5D, 0xD38, 0xD11, 0xCEA, 0xCC2, 0xC99,
   0xC70, 0xC46, 0xC1B, 0xBEF, 0xBC3, 0xB97, 0xB6A, 0xB3C,
   0xB0E, 0xADF, 0xAB0, 0xA81, 0xA51, 0xA20, 0x9F0, 0x9BF,
   0x98E, 0x95C, 0x92B, 0x8F9, 0x8C7, 0x895, 0x863, 0x831,
   0x7FF, 0x7CC, 0x79A, 0x768, 0x736, 0x704, 0x6D2, 0x6A1,
   0x66F, 0x63E, 0x60D, 0x5DD, 0x5AC, 0x57C, 0x54D, 0x51E,
   0x4EF, 0x4C1, 0x493, 0x466, 0x43A, 0x40E, 0x3E2, 0x3B7,
   0x38D, 0x364, 0x33B, 0x313, 0x2EC, 0x2C5, 0x2A0, 0x27B,
   0x257, 0x234, 0x212, 0x1F0, 0x1D0, 0x1B1, 0x192, 0x175,
   0x158, 0x13D, 0x123, 0x109, 0x0F1, 0x0DA, 0x0C4, 0x0AF,
   0x09B, 0x089, 0x077, 0x067, 0x058, 0x04A, 0x03D, 0x031,
   0x027, 0x01E, 0x016, 0x00F, 0x009, 0x005, 0x002, 0x001,
   0x000, 0x001, 0x002, 0x005, 0x009, 0x00F, 0x016, 0x01E,
   0x027, 0x031, 0x03D, 0x04A, 0x058, 0x067, 0x077, 0x089,
   0x09B, 0x0AF, 0x0C4, 0x0DA, 0x0F1, 0x109, 0x123, 0x13D,
   0x158, 0x175, 0x192, 0x1B1, 0x1D0, 0x1F0, 0x212, 0x234,
   0x257, 0x27B, 0x2A0, 0x2C5, 0x2EC, 0x313, 0x33B, 0x364,
   0x38D, 0x3B7, 0x3E2, 0x40E, 0x43A, 0x466, 0x493, 0x4C1,
   0x4EF, 0x51E, 0x54D, 0x57C, 0x5AC, 0x5DD, 0x60D, 0x63E,
   0x66F, 0x6A1, 0x6D2, 0x704, 0x736, 0x768, 0x79A, 0x7CC,
   */
};
//-----------------------------------------------------------------------------
// SPI0_ISR
//-----------------------------------------------------------------------------
//
// SPI0 ISR Content goes here. Remember to clear flag bits:
// SPI0CN0::MODF (Mode Fault Flag)
// SPI0CN0::RXOVRN (Receive Overrun Flag)
// SPI0CN0::SPIF (SPI# Interrupt Flag)
// SPI0CN0::WCOL (Write Collision Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (SPI0_ISR, SPI0_IRQn)
{
	   static unsigned char command;
	   static unsigned char state = 0;
	   SCON0_TI = 1;
	   if (SPI0CN0_WCOL == 1)
	   {
	      // Write collision occurred
	      SPI0DAT = ERROR_OCCURRED;        // Indicate an error occurred
	      SPI0CN0_WCOL = 0;                 // Clear the Write collision flag
	   }
	   else if(SPI0CN0_RXOVRN == 1)
	   {
	      // Receive overrun occurred
	      SPI0DAT = ERROR_OCCURRED;        // Indicate an error occurred
	      SPI0CN0_RXOVRN = 0;               // Clear the Receive Overrun flag
	   }
	   else
	   {
	     //  SPI0CN0_SPIF caused the interrupt
	      // Some commands are single-byte commands (SLAVE_LED_ON/SLAVE_LED_OFF)
	      // For multiple-byte commands, use the state to determine action
	      // <state> == 0: new transfer; a command is being received
	      // <state> == 1: writing/reading data
	      if(state == 0)
	      {
	    	 command = SPI0DAT;            // Read the command
	         switch(command)
	         {
	         	case TEMP_OUT:
	         	     SPI0DAT = SPI0_TEMP_OUT_DATA_2;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT2:
	         	     SPI0DAT = SPI0_GYRO_OUT2_DATA_2;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT:
	         	     SPI0DAT = SPI0_GYRO_OUT_DATA_H;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case SERIAL_NUM:
	         	     SPI0DAT = SPI0_SERIAL_NUM_DATA;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	            default:
	               state = 0;
	         }

	      }
	      else if(state == 1)
	      {
	    	 SPI_Data = SPI0DAT;
	         switch(command)
	         {
	         	case TEMP_OUT:
	         	     SPI0DAT = SPI0_TEMP_OUT_DATA_1;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT2:
	         	     SPI0DAT = SPI0_GYRO_OUT2_DATA_1;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT:
	         	     SPI0DAT = SPI0_GYRO_OUT_DATA_L;
	         	     if (SIN_COS == true){
						 SIN++;
						 if(SIN>=256)SIN=0;
						 GYRO_0 = SINE_TABLE[SIN];
						 GYRO_0 /=8;
						 SPI0_GYRO_OUT_DATA_L   =  GYRO_0;
						 SPI0_GYRO_OUT_DATA_H   =  GYRO_0>>8;
						 GYRO_0 = 0x0000;
	         	     }
	         	    if(REZIM_3==1){
	         	    	GYRO_0 = GYRO_0+16;
	         	    	if (GYRO_0 > 4200)GYRO_0 = 0;
	         	    	SPI0_GYRO_OUT_DATA_L = GYRO_0;
	         	    	SPI0_GYRO_OUT_DATA_H = GYRO_0>>8;
	         	    }
	         	    if(REZIM_3==2){
	         	    	GYRO_0 = GYRO_0-16;
	         	        if (GYRO_0 < -4200)GYRO_0 = 0;
	         	    	SPI0_GYRO_OUT_DATA_L = GYRO_0;
	         	        SPI0_GYRO_OUT_DATA_H = GYRO_0>>8;
	         	    }
	         	   if(REZIM_3==3){
	         	   	   GYRO_0 = GYRO_0-16;
	         	   	   if (GYRO_0 < -4200)GYRO_0 = 4200;
	         	   	   SPI0_GYRO_OUT_DATA_L = GYRO_0;
	         	   	   SPI0_GYRO_OUT_DATA_H = GYRO_0>>8;
	         	   }
	         	   state = 0;              // Move to State 1 to continue to send
	         		                                   // data to the Master (multiple bytes).
	         	   break;
	             default:
	               state = 0;
	         }
	      }
	      SPI0DAT = 0x00;
	      SPI0CN0_SPIF = 0;                 // Clear the SPIF0 flag
	   }
}
SI_INTERRUPT (SPI1_ISR, SPI1_IRQn)
{
	   static unsigned char command;
	   static unsigned char state = 0;
	   if (SPI1CN0_WCOL == 1)
	   {
	      // Write collision occurred
	      SPI1DAT = ERROR_OCCURRED;        // Indicate an error occurred
	      SPI1CN0_WCOL = 0;                 // Clear the Write collision flag
	   }
	   else if(SPI1CN0_RXOVRN == 1)
	   {
	      // Receive overrun occurred
	      SPI1DAT = ERROR_OCCURRED;        // Indicate an error occurred
	      SPI1CN0_RXOVRN = 0;               // Clear the Receive Overrun flag
	   }
	   else
	   {
	     //  SPI0CN0_SPIF caused the interrupt
	      // Some commands are single-byte commands (SLAVE_LED_ON/SLAVE_LED_OFF)
	      // For multiple-byte commands, use the state to determine action
	      // <state> == 0: new transfer; a command is being received
	      // <state> == 1: writing/reading data
	      if(state == 0)
	      {

	    	 command = SPI1DAT;            // Read the command
	    //    array_index = 0;              // Reset the array index

	         switch(command)
	         {
	         	case TEMP_OUT:
	         	     SPI1DAT = SPI0_TEMP_OUT_DATA_2;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT2:
	         	     SPI1DAT = SPI0_GYRO_OUT2_DATA_2;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT:
	         	     SPI1DAT = SPI1_GYRO_OUT_DATA_H;
	         	     state = 1;              // Move to State 1 to continue to send
	         		                         // data to the Master (multiple bytes).
	         	     break;
	         	case SERIAL_NUM:
	         	     SPI1DAT = SPI0_SERIAL_NUM_DATA;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	            default:
	               state = 0;
	         }
	      }
	      else if(state == 1)
	      {
	    	  SPI_Data = SPI1DAT;
	         switch(command)
	         {
	         	case TEMP_OUT:
	         	     SPI1DAT = SPI0_TEMP_OUT_DATA_1;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT2:
	         	     SPI1DAT = SPI0_GYRO_OUT2_DATA_1;
	         	     state = 0;              // Move to State 1 to continue to send
	         		                                       // data to the Master (multiple bytes).
	         	     break;
	         	case GYRO_OUT:
	         	     SPI1DAT = SPI1_GYRO_OUT_DATA_L;
	         	     if (SIN_COS == true){
	         	    	COS++;
						 if(COS>=256)COS=0;
						 GYRO_1 = SINE_TABLE[COS];
						 GYRO_1 /=8;
						 SPI1_GYRO_OUT_DATA_L   =  GYRO_1;
						 SPI1_GYRO_OUT_DATA_H   =  GYRO_1 >>8;
						 GYRO_1 = 0x0000;
	         	     }
	         	    if(REZIM_3==1){
	         	      GYRO_1 = GYRO_1-16;
	        	      if (GYRO_1 < -4200)GYRO_1 = 0;
	        	      SPI1_GYRO_OUT_DATA_L = GYRO_1;
	         	   	  SPI1_GYRO_OUT_DATA_H = GYRO_1>>8;
	         	   	}
	         	   	if(REZIM_3==2){
	         	   	  GYRO_1 = GYRO_1+16;
	         	   	  if (GYRO_1 > 4200)GYRO_1 = 0;
	         	   	  SPI1_GYRO_OUT_DATA_L = GYRO_1;
	         	   	  SPI1_GYRO_OUT_DATA_H = GYRO_1>>8;
	         	    }
	         	   if(REZIM_3==3){
	         	   	    GYRO_1 = GYRO_1+16;
	         	   	    if (GYRO_1 > 4200)GYRO_1 = -4200;
	         	   	    SPI1_GYRO_OUT_DATA_L = GYRO_1;
	         	   	    SPI1_GYRO_OUT_DATA_H = GYRO_1>>8;
	         	   	}
	         	    state = 0;              // Move to State 1 to continue to send
	         		                                   // data to the Master (multiple bytes).
	         	    break;
	             default:
	               state = 0;
	         }
	      }
	      SPI1DAT = 0x00;
	      SPI1CN0_SPIF = 0;                 // Clear the SPIF0 flag
	   }
}
