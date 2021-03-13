/*
 * 
 */
#define F_CPU 16000000UL //16MHz
#define BAUD 9600
//#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/setbaud.h> // Biblioteca que calcula o baudrate

/*
 * A função usart_init inicializa os registradores que serão utilizadas
 * para a habilitação do uso do TX, usando o baudrate calculado pela 
 * biblioteca setbaud.h para a F_CPU = 16MHz
 */
void usart_init()
{
  /*
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);
  */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0B |= (1 << TXEN0); // Habilita TX
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Tamanho do caractere = 8bits
}
/*
 * Esta função realiza o envio do data pela serial
 */
void usart_send(char data)
{
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}
int main()
{
  char data = '1'; //Mensagem a ser enviada
  usart_init();
  usart_send(data);
  while(1);
  return 0;
}
