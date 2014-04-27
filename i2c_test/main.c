#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <USI_TWI_Master/USI_TWI_Master.h>

int main( void ) {
   DDRB |= _BV(DDB1);
   PORTB &= ~_BV(PORTB1);
   for(;;) {
      PORTB ^= _BV(PORTB1);
      _delay_ms(1000);
   }
}

