#include "motor.h"

#include "PID.h"

Motor::Motor(int motor_a, int motor_b, int coder_VCC, int coder_a, int coder_b) {
    // initialize the motor pins
    // the motor pins must connect to the arduino digial pin with pwm-controlling
    pinMode(motor_a, OUTPUT);
    pinMode(motor_b, OUTPUT);

    // the coder_VCC pin connect to the arduino digital pin
    pinMode(coder_VCC, INPUT);

    // the coder_a and coder_b pins connect to the arduino digital pin to read the coder message
    pinMode(coder_a, INPUT);
    pinMode(coder_b, INPUT); 
    
    // assign all the motor variables
    motor_a_ = motor_a;
    motor_b_ = motor_b;
    coder_VCC_ = coder_VCC;
    coder_a_ = coder_a;
    coder_b_ = coder_b;
}


// this function has sorts of problems:
// the first getCurrentSpeed calculation will not be so accurate for the bad presion of last_time_us_
// the the fuction pointer has a liitle problem s.t there is a complie error 
void Motor::initiate() {
    attachInterrupt(coder_a_, Motor::coderA, RISING);
    attachInterrupt(coder_b_, Motor::coderB, RISING);
    cur_time_us_ = last_time_us_ = micros();
}

void Motor::run(double expected_speed) {
    double cur_speed = getCurrentSpeed();
    int pwm = get_PID_internal(cur_speed, expected_speed);
    if (expected_speed > 0) {
        motorForward(pwm);
    } else {
        motorBackward(pwm);
    }
    return ;
}

void Motor::stop() {
    motorStop(0);
    return ;
}

double Motor::getCurrentSpeed() {
    // unsigned long last_us = 0;
	unsigned long cur_time_us_ = micros();
	double cur_speed = MODULUS * double(pulse_count_) / (cur_time_us_ - last_time_us_);
	last_time_us_ = cur_time_us_;
	pulse_count_ = 0;
	return cur_speed;
}	
