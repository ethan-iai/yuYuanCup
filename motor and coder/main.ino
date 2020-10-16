#include "CoderMotor.h"

#define LEFT_FRONT_PIN

CoderMotor left_front_motor = Motor(args...., &left_back_count);
CoderMotor right_front_motor = Motor(args..., &right_front_count);
CoderMotor left_back_motor = Motor(args..., &left_back_count);
CoderMotor right_back_motor = Motor(args...., &right_back_count);

volatile long left_front_count = 0;
volatile long right_front_count = 0;
volatile long left_back_count = 0;
volatile long right_back_count = 0;

void left_front_postive() { positive(... , &left_front_count) };
void left_front_negative() { negative(..., &left_front_count) };

void right_front_postive() { positive(... , &right_front_count) }; 
void right_front_negative() { negative(..., &right_front_count) };

void left_back_postive() { positive(... , &left_back_count) };
void left_back_negative() { negative(..., &left_back_count) };

void right_back_postive() { positive(... , &right_back_count) };
void right_back_negative() { negative(..., &right_back_count) };

void positive(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)++;
    else (*count_ptr)--;
}

void negative(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)--;
    else (*count_ptr)++;
}

void attachInterrupts()
{   
    // for every coder 
    // every coder has left_pin and right_pin
        attachInterrupt(positive_pin, ..._..._positive, RISING);
        attachInterrupt(negative_pin, ..._..._negative, RISING);
}

void setup()
{
    
    attachInterrupts();
    // ...
}

void loop()
{
    // ...   
}