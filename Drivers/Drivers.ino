re#include <avr/io.h> //Bibiloteca com as funções de E/S dos microcontroladores AVR
#include <util/delay.h> //Biblioteca com as funções de delay, como a _delay_ms, utilizada ao longo do código
#include <stdbool.h> //Bliblioteca com as funções booleanas, como true e false, utilizadas ao longo do código

#define INPUT false
#define OUTPUT true

#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

/*
 * Resumo: Esta função zera os registradores
 * Parâmetros: None.
 */
void initialize()
{
  DDRB = 0; // --> Limpa o registrador DDRB
  DDRC = 0; // --> Limpa o registrador DDRC
  DDRD = 0;  // --> Limpa o registrador DDRD
}
/*
 * Resumo: 
 *        Parâmetros:
 *                  - int pin: pino que será configurado. 
 *                             --> 0~7.
 *                  - int port: Porta que dejesa ativar.
 *                             --> PORTB == 1;
 *                             --> PORTC == 2;
 *                             --> PORTD == 3.
 *                  - bool value:
 *                             --> OUTPUT; 
 *                             --> INPUT.
 */
void mode(int pin, int port, bool value)
{
  if (value == OUTPUT){ // --> Verifica se está setando como saída
    if (port == PORT_B){ // --> Verifica se o registrador selecionado é o DDRB
      DDRB |= (1 << pin); // --> Seta o registrador na posição DDBX = pin como saída
    }
    else if (port == PORT_C){ // --> Verifica se o registrador selecionado é o DDRC
      DDRC |= (1 << pin); // --> Seta o registrador na posição DDCX = pin como saída
    }
    else if (port == PORT_D){ // --> Verifica se o registrador selecionado é o DDRD
      DDRD |= (1 << pin); // --> Seta o registrador na posição DDDX = pin como saída
    }
  }
   else if (value == INPUT){ // --> Verifica se está setando como entrada
    if (port == PORT_B){ // --> Verifica se o registrador selecionado é o DDRB
      DDRB &= ~(1 << pin); // --> Seta o registrador na posição DDBX = pin como saída
      }
    else if (port == PORT_C){ // --> Verifica se o registrador selecionado é o DDRC
      DDRC &= ~(1 << pin); // --> Seta o registrador na posição DDCX = pin como saída
    }
    else if (port == PORT_D){ // --> Verifica se o registrador selecionado é o DDRD
      DDRD &= ~(1 << pin); // --> Seta o registrador na posição DDDX = pin como saída
    }
  }
}
/*
 * Resumo: 
 *        Parâmetros:
 *                  - int pin: pino que será configurado. 
 *                             --> 0~7.
 *                  - char port[1]: Porta que dejesa ativar.
 *                             --> PORTB == 1;
 *                             --> PORTC == 2;
 *                             --> PORTD == 3.
 *                  - int value:
 *                             --> 1 == Nível alto; 
 *                             --> 0 == Nível baixo.
 */
void setPin(int pin, int port, int value)
{
  if (value == 1){ // --> Verifica se está setando como nível lógico alto
    if (port == PORT_B){ // --> Verifica se a porta selecionada é a PORTB
      PORTB |= (1 << pin); // --> Seta a porta PORTBX = pin como nível alto
    }
    else if (port == PORT_C){ // --> Verifica se a porta selecionada é a PORTC
      PORTC |= (1 << pin); // --> Seta a porta PORTCX = pin como nível alto
    }
    else if (port == PORT_D){ // --> Verifica se a porta selecionada é a PORTD
      PORTD |= (1 << pin); // --> Seta a porta PORTDX = pin como nível alto
    }
  }
  else if (value == 0){ // --> Verifica se está setando como nível lógico baixo
    if (port == PORT_B){ // --> Verifica se a porta selecionada é a PORTB
      PORTB &= ~(1 << pin); // --> Seta a porta PORTBX = pin como nível alto
    }
    else if (port == PORT_C){ // --> Verifica se a porta selecionada é a PORTC
      PORTC &= ~(1 << pin); // --> Seta a porta PORTCX = pin como nível baixo
    }
    else if (port == PORT_D){ // --> Verifica se a porta selecionada é a PORTD
      PORTD &= ~(1 << pin); // --> Seta a porta PORTDX = pin como nível baixo
    }
  }
}
/*
 * Resumo: 
 *        Parâmetros:
 *                  - int pin: pino que será configurado. 
 *                             --> 0~7.
 *                  - char port[1]: Porta que dejesa ler.
 *                             --> PORTB == 1;
 *                             --> PORTC == 2;
 *                             --> PORTD == 3.
 */
bool readPin(int pin, int port)
{
  if (port == PORT_B){ // --> Verifica se a porta selecionada é a PORTB
    if (PINB & (1 << pin) == (1 << pin))return true; // --> Verifica se o PORTBX = pin em nível alto
    else return false;
  }
  else if (port == PORT_C){ // --> Verifica se a porta selecionada é a PORTC
    if (PINC & (1 << pin) == (1 << pin)) return true; // --> Verifica se o PORTCX = pin em nível alto
    else return false;
  }
  else if (port == PORT_D){ // --> Verifica se a porta selecionada é a PORTD
    if (PIND & (1 << pin) == (1 << pin)) return true; // --> Verifica se o PORTDX = pin em nível alto
    else return false;
  }
}
int main()
{
  initialize();
  mode(5, 1, 1);
  while (1){
    if(readPin(0,1)== true){
      setPin(5,1,1);
      _delay_ms(200);
      }
      else{
        setPin(5,1,0);
        _delay_ms(200);
      }
  }
  return 0;
}
