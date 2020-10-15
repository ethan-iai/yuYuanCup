#ifndef MY_ARDUINO_H_
#define MY_ARDUINO_H_

#define INPUT 0
#define OUTPUT 1

#define HIGH 1
#define LOW 0

#define RISING 0

void pinMode(int pin, int mode);
void analogWrite(int pin, int value);
void digitalWrite(int pin, int value);

int digitalRead(int pin);

unsigned long micros();
unsigned long millis();

#endif