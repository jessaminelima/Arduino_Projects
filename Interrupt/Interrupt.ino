/*
 * Este código realiza o toggle do LED built-in a cada 1.5s
 * E o estado do mesmo muda a cada interrupção
 * 
 * As interrupções são dos tipos:
 *  PCINT --> Por meio do PB2
 *  INT --> Por meio do PD2
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*
 * A função gpio_init inicializa os registradores das GPIOs que serão utilizadas
 */
void gpio_init(){
    
  DDRD &= ~(1 << DDD2); //PCINT18(PD2) setado como entrada
  PORTD |= (1 << PORTD2); //Pull-up no PCINT18(PD2)
  
  DDRD &= ~(1 << DDB2); //PCINT18(PB2) setado como entrada
  PORTB |= (1 << PORTB2); //Pull-up no PCINT2(PB2)
  
  DDRB |= (1 << DDB5); // PCINT5(PB5) setado como saída
}
/*
 * A função interrupt_init configura os registradores para que
 * seja possível detectar as interrupções do tipo PCINT e INT
 */
void interrupt_init(){
  cli(); // Desabilita todas as interrupções
  
  SREG |= (1 << SREG_I); // Bit I(7) do SREG --> ativador global de interrupções

  EIMSK |= (1 << INT0); // Mascara referente ao INT0
  EICRA |= (1 << ISC01); // Configura para borda de descida
  
  PCICR |= (1 << PCIE0); // Habilita a detecção interrupções no por mudança em qual quer PCINT0~7
  PCMSK0 |= (1 << PCINT2); // Seleciona a ativação de interrupção no PCINT2(PB2)
  
  sei(); // Habilita todas as interrupções
}

int main(){
  gpio_init();
  interrupt_init();
  while(1){
    PORTB ^= (1 << PORTB5); // Toggle o LED Built-in
    _delay_ms(1500);
  }
}
/*
 * Rotina de interrupção tipo PCINT
 * Onde sempre que ocorrer uma interrupção o LED mudará de estado
 */
ISR(PCINT0_vect){
  PORTB ^= (1 << PORTB5);
}
/*
 * Rotina de interrupção tipo INT
 * Onde sempre que ocorrer uma interrupção o LED mudará de estado
 */
ISR(INT0_vect){
  PORTB ^= (1 << PORTB5);
}
