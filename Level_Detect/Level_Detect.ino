#include <avr/io.h>
#include <util/delay.h>

/*
 * This program turn on Pin 13, if Pin 8 is High
 */
int main()
{
  DDRB = 0; // 0000 0000
  DDRB = (1 << DDB5); // 0010 0000

  while (1){
  
    if (PINB & (1 << PINB0) == (1 << PINB0)){ // --> Readin Pin 8
      PORTB |= (1 << PORTB5); // 0010 0000 --> Set Pin 13 as High
      _delay_ms(500);
    }
    
    else{
      PORTB &= ~(1 << PORTB5); // 0010 0000 --> Set Pin 13 as LOW
      _delay_ms(500);
    }    
  }   
  return 0;
}
