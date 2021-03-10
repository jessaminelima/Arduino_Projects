/*
 * Este código trabalha a interrupção por time compare utilizando um TIMER(TIMER0)
 * de 8bits (contagem de 0 a 255)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
volatile int contador = 0;

/*
 * A função timer_init configura os registradores necessários para
 * que seja possível realizar interrupções por time compare, onde
 * OCR0 determina o valor máximo da contagem do registrador TCNT0.
 */
void timer_init()
{ 
  cli(); // Desabilidata todas as interrupções
  SREG |= (1 << 7); // Bit I(7) do SREG --> ativador global de interrupções
  
  TCCR0A |= (1 << WGM01); // Habilita o modo CTC
  TCCR0B |= (1 << CS01); // 8 prescaler
  TIMSK0 |= (1 << OCIE0A); // Habilitlita a interrupção por time compare
  OCR0A = 200;
  TCNT0 = 0;
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
 * A função ISR trata-se da rotina de interrução por time compare
 * É inializada a cada vez que o timer alcança o valor máximo configurado, 
 * o que seria a cada 0.1us
 */
ISR(TIMER0_COMPA_vect)
{
  if(contador == 20000) // Contador == 20000 a cada 2 segundos
  {
    PORTB ^= (1 << PORTB5); //Muda o estado do PB5
    contador = 0;
  }
  else contador++;
}
