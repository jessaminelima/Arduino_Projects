#include <avr/io.h>
#include <util/delay.h>
/*
 * This Program Toogle the LED built-in (Pin 13)
 */
int main()
{
  DDRB = 0;
  DDRB |= (1 << DDB5);

  while (1){
      PORTB ^= (1 << PORTB5);
      _delay_ms(200);
  }
  return 0;
}
