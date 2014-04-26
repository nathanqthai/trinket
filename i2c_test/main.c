/*****************************************************************************
 *
 * Atmel Corporation
 *
 * File              : main.c
 * Compiler          : AVRGCC Toolchain version 3.4.2
 * Revision          : $Revision: 992 $
 * Date              : $Date: 2013-11-07 $
 * Updated by        : $Author: Atmel $
 *
 * Support mail      : avr@atmel.com
 *
 * Supported devices : All device with USI module can be used.
 *                     The example is written for the ATmega169, ATtiny26 & ATtiny2313
 *
 * AppNote           : AVR310 - Using the USI module as a TWI Master
 *
 * Description       : Example of how to use the driver for TWI master
 *                     communication with the USI module.
 *                     This code reads PORTD and sends the status to the TWI slave.
 *                     Then it reads data from the slave and puts the data on PORTB.
 *                     To run the example use STK500 and connect PORTB to the LEDS,
 *                     and PORTD to the switches.
 *
 ****************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USI_TWI_Master.h"

#define SLAVE_ADDR  0x77
#define MESSAGEBUF_SIZE       4

unsigned char TWI_Act_On_Failure_In_Last_Transmission ( unsigned char TWIerrorMsg )
{
   // A failure has occurred, use TWIerrorMsg to determine the nature of the failure
   // and take appropriate actions.
   // Se header file for a list of possible failures messages.
   asm("nop");
   return TWIerrorMsg;
}

int main( void )
{
   unsigned char messageBuf[MESSAGEBUF_SIZE];
   unsigned char TWI_targetSlaveAddress, temp;
   DDRB |= _BV(DDB1);

   USI_TWI_Master_Initialise();

   sei();

   TWI_targetSlaveAddress   = SLAVE_ADDR;

   for(;;)
   {
      messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT);
      messageBuf[1] = TWI_CMD_MASTER_READ;
      temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2 );
      messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT);
      do
         temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2 );
      while (USI_TWI_Get_State_Info() == USI_TWI_NO_ACK_ON_ADDRESS);


      if (!temp)    // One of the operations failed.
      {             // Use TWI status information to detemine cause of failure and take appropriate actions.
         TWI_Act_On_Failure_In_Last_Transmission( USI_TWI_Get_State_Info( ) );
         asm("nop"); // Put own code here.
      }
   }
}
}

