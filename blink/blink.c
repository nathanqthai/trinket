#include <avr/io.h>
#include <util/delay.h>

int main(void) {
   DDRB |= _BV(DDB1);
   while(1) {
      PORTB |= _BV(PORTB1);
      _delay_ms(1000);
      PORTB &= ~_BV(PORTB1);
      _delay_ms(1000);
   }
   return 0;
}
