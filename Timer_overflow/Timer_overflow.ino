/*
 * Este código trabalha a interrupção por overflow utilizando um TIMER(TIMER0)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

/*
 * A função timer_init configura os registradores necessários para
 * que seja possível realizar interrupções por overflow.
 */
void timer_init()
{ 
  cli(); // Desabilidata todas as interrupções
  SREG |= (1 << 7); // Bit I(7) do SREG --> ativador global de interrupções
  
  TCCR1B |= (1 << CS11); // 8 prescaler
  TIMSK1 |= (1 << TOIE1); // Habilitlita a interrupção por overflow
  TCNT1 = 0;
  sei();
}

/*
 * A função gpio_init configura os registradores
 * das GPIO que se deseja utilizar.
 */
void gpio_init()
{
  DDRB |= (1 << DDB5); 
  PORTB &= ~(1 << PORTB5);
}
int main()
{
  gpio_init();
  timer_init();
  while(1);
  return 0;
}

/*
 * A função ISR trata-se da rotina de interrução por overflow
 * É inializada a cada vez que o timer alcança o valor máximo do timer
 */
ISR(TIMER0_OVF_vect)
{
    PORTB ^= (1 << PORTB5); //Muda o estado do PB5
    TCNT1 = 0;
}
