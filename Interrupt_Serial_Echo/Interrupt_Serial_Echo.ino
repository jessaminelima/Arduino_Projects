/*
 * Este código realiza recebe uma inforção na serial e realiza o echo, 
 * envio de uma informação pela serial igual a informação recebida e
 * caso a informação seja 't', o pino PB5 irá para nível lógico alto, 
 * caso contrário ele permanecerá em nível baixo.
 */
 
#define F_CPU 16000000UL //16MHz
#define BAUD 9600
//#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h> // Biblioteca que calcula o baudrate

volatile char buf;
/*
 * A função gpio_init inicializa os registradores que serão utilizadas
 * para a habilitação do pino PB5
 */
void gpio_init()
{
  DDRB |= (1 << DDB5);
  PORTB &= ~(1 << PORTB5);
}
/*
 * A função usart_init inicializa os registradores que serão utilizadas
 * para a habilitação do uso do RX, TX e da interrupção pelo RX, usando
 * o baudrate calculado pela biblioteca setbaud.h para a F_CPU = 16MHz
 */
void usart_init()
{
  cli(); // Desabilidata todas as interrupções
  SREG |= (1 << SREG_I); // Bit I(7) do SREG --> ativador global de interrupções
  
  /*
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);
  */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Habilita RX, TX e interrupção quando recebe um dado
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Tamanho do caractere = 8bits  
  
  sei();// Habilidata todas as interrupções
}

int main()
{
  interrupt_init();
  gpio_init();
  usart_init();
  while(1);
  return 0;
}
/*
 * Rotina de interrupção
 * Onde sempre que for recebido algo  ocorrerá uma interrupção
 * de modo que a informação recebida será enviada de volta para
 * a serial e caso a informação seja 't', o PB5 irá para nível 
 * lógico alto caso, contrário  permanecerá em nível baixo.
 */
ISR(USART_RX_vect)
{
    while(!(UCSR0A & (1 << RXC0)));
    buf = UDR0; //Recebe dado
    
    if(buf == 't') // Se recebe t 
    {
      PORTB |= (1 << PORTB5); // Aciona o PB5
    }
    else
    {
      PORTB &= ~(1 << PORTB5);
    }
    while(!(UCSR0A & (1 << UDRIE0)));
    UDR0 = buf; // Transmite dado recebido
}
