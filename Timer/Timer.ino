/*
 *  Este programa trabalha a interrupção por time compare
 *  utilizando um TIMER (TIMER1) de 16 bits (contagem de 0 a 65535)
 *  Frequência da CPU = 16MHz
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 * A função timer_init configura os registradores necessários para
 * que seja possível realizar interrupções por time compare, onde
 * OCR1 determina o valor máximo da contagem do registrador TCNT1.
 */
void timer_init()
{
  cli(); // Desabilidata todas as interrupções
  SREG |= (1 << SREG_I); // Bit I(7) do SREG --> ativador global de interrupções
  
  TCNT1 = 0; // Inicia o contador em 0
  
  OCR1A = 0xF424; // Seta o valor máximo da comparação = 62500
  TCCR1B |= (1 << WGM12); // Habilita o modo CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // Habilitlita a interrupção por time compare
  
  sei();// Habilidata todas as interrupções
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
 * A função ISR trata-se da rotina de interrução por timer compare
 * É inializada a cada vez que o timer alcança o valor máximo configurado
 */
ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << PORTB5); //Muda o estado do PB5
  TCNT1 = 0; // Garante que o contador reset
}
