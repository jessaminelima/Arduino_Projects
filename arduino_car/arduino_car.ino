#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // RX, TX
char command = "";
int cont = 0;

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, INPUT); // echoPin
  pinMode(10, OUTPUT);  //triggerPin
  
  Serial.begin(9600);
  mySerial.begin(9600); 
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
void front()
{
    // Vai para frente
    digitalWrite(9, LOW); //A-IA
    digitalWrite(8, HIGH); //A-IB
    digitalWrite(7, LOW); //B-IA
    digitalWrite(6, HIGH); //B-IB  
}
void back()
{
    // Vai para tras
    digitalWrite(9, HIGH); //A-IA
    digitalWrite(8, LOW); //A-IB
    digitalWrite(7, HIGH); //B-IA
    digitalWrite(6, LOW); //B-IB
}
void stoped()
{
    // Para o carrinho
    digitalWrite(9, LOW); //A-IA
    digitalWrite(8, LOW); //A-IB
    digitalWrite(7, LOW); //B-IA
    digitalWrite(6, LOW); //B-IB
}
void right()
{
    // Vai para a direita
    digitalWrite(9, LOW); //A-IA
    digitalWrite(8, HIGH); //A-IB
    digitalWrite(7, LOW); //B-IA
    digitalWrite(6, LOW); //B-IB
}
void left()
{
    // Vai para a esquerda
    digitalWrite(9, LOW); //A-IA
    digitalWrite(8, LOW); //A-IB
    digitalWrite(7, LOW); //B-IA
    digitalWrite(6, HIGH); //B-IB
}
void dodge()
{
    stoped();
    delay(500); // Wait 1s
    if (cont < 3)
    {
        right();
        delay(500); // Wait 1s
        cont = (cont + 1);
    }
    else
    {
        stoped();
        delay(500); // Wait 1s
        left();
        delay(500); // Wait 1s
        cont = 0;
    }
}
void loop()
{  
    if (0.01723 * readUltrasonicDistance(10, 11) > 20.0)
    {
        stoped();
        cont = 0;
        if (mySerial.available()) 
        {
            command = (char)mySerial.read();
            Serial.println(command);
            if (command == 'f')
            {
                // Vai para frente
                front();
                delay(1000); // Wait 1s
                stoped();     
            }
            if (command == 'b')
            {
                // Vai para tras
                back();
                delay(1000); // Wait 1s
                stoped();
            }
            if (command == 'r')
            {
                // Vai para a direita
                right();
                delay(500); // Wait 1s
                stoped();
            }
            if (command == 'l')
            {
                // Vai para a esquerda
                left();
                delay(500); // Wait 1s
                stoped();
            }
            if(command == 'a')
            {
                while (command != 'm')
                {
                    // Vai para frente
                    command == "";
                    delay(1000); // Wait 1s
                    command = (char)mySerial.read();
                    if (0.01723 * readUltrasonicDistance(10, 11) > 20.0)
                    {
                        front();
                    }
                    else
                    {
                        dodge();
                    }
                }
            }
            command == "";
        }
    }
    else
    {
        dodge();
    }
}
