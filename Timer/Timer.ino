/*
 *  Frequência da CPU = 16MHz
 *  Período = 1/frequência
 *  Resolução TIMER0 e TIMER2 = 8 bits --> conta de 0 a 255
 *  Resolução TIMER1 = 16 bits --> conta de 0 a 65535
 *  
 *  Assim para prescale de 1024 usando TIMER1:
 *  Frequência = 16MHz/1024 = 15625 Hz
 *  Tempo para contar 1 bit = 1/15625 = 6,4e-5s
 *  Tempo para contar até 0xF424 = 6,4e-5*62500 = 4s
 *
 *  Assim para prescale de 1024 usando TIMER1:
 *  Frequência do timer = 16MHz/1024 = 15625 Hz
 *  Tempo para contar 1 bit = 1/15625 = 6,4e-5s
 *  Tempo para contar até 0xB5EF = 6,4e-5*46575 = 3s
 *  
 *  Assim para prescale de 1024 usando TIMER1:
 *  Frequência = 16MHz/1024 = 15625 Hz
 *  Tempo para contar 1 bit = 1/15625 = 6,4e-5s
 *  Tempo para contar até 0x7A12 = 6,4e-5*31250 = 2s
 *  
 *  Assim para prescale de 1024 usando TIMER1:
 *  Frequência = 16MHz/1024 = 15625 Hz
 *  Tempo para contar 1 bit = 1/15625 = 6,4e-5s
 *  Tempo para contar até 0x3D09 = 6,4e-5*15325 = 1s
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
  
  OCR1A = 0x7FFE; // Setar o valor máximo da comparação
  TCCR1B |= (1 << WGM12);   // Habilita o modo CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);// Habilitlita a interrupção por timer compare
  
  sei();// Habilidata todas as interrupções
}

/*
 * A função gpio_init configura os registradores
 * das GPIO que se deseja utilizar.
 */
void gpio_init(){
  DDRB |= (1 << DDB5); 
  PORTB &= ~(1 << PORTB5);
}
int main(){
  gpio_init();
  timer_init();
  while(1);
  return 0;
}
/*
 * A função ISR trata-se da rotina de interrução por timer compare
 */
ISR(TIMER1_COMPA_vect){
  PORTB^=(1<<PORTB5);
  TCNT1 = 0; // Garante que o contador reset
}
