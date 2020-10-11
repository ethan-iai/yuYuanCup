#ifndef MY_ARDUINO_H_
#define MY_ARDUINO_H_

#define INPUT 0
#define OUTPUT 1

#define RISING 0

void pinMode(int pin, int mode);
void analogWrite(int pin, int value);
void attachInterrupt(int pin, void* function, int mode);

int digitalRead(int pin);

unsigned long micros();
unsigned long millis();

#endif