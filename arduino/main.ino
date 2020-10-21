#include "CoderMotor.h"

volatile long left_front_count = 0;
volatile long right_front_count = 0;
volatile long left_back_count = 0;
volatile long right_back_count = 0;

// call the constructor of CoderMotor class
// CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr);
CoderMotor left_front_motor = CoderMotor(args...., &left_back_count);
CoderMotor right_front_motor = CoderMotor(args..., &right_front_count);
CoderMotor left_back_motor = CoderMotor(args..., &left_back_count);
CoderMotor right_back_motor = CoderMotor(args...., &right_back_count);

// call the positive() and negative() listed below
// if the positive pin of the left front coder connects to arduino no.10 pin
// call left_front_positive { postive(10, &left_front_count)};  
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

void initIO()
{
    // initiate the IO pins
}

void attachInterrupts()
{   
    // for every coder 
    // every coder has positive_pin and negative_pin
        attachInterrupt(positive_pin, ..._..._positive, RISING);
        attachInterrupt(negative_pin, ..._..._negative, RISING);
}

void setup()
{
    initIO();   
    attachInterrupts();
    // ...
}

void loop()
{
    // ...   
}