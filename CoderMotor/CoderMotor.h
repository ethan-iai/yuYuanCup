#ifndef CODERMOTOR_H_
#define CODERMOTOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Coder.h"
#include "PIDController.h"

class CoderMotor {
private:
	// motor_a and motor_b are two motor pins
	int PWM_pin_; // PWM output pin
	int forward_pin_; // if high, motor runs forward
	int backward_pin_;

	Coder coder_; //  coder of the motor 
	PIDController PIDController_;

	void motorForward(int pwm) { digitalWrite(forward_pin_, HIGH); digitalWrite(backward_pin_, LOW); analogWrite(PWM_pin_, pwm); };
	void motorStop(int pwm) { digitalWrite(forward_pin_, LOW); digitalWrite(backward_pin_, LOW); analogWrite(PWM_pin_, pwm); }; 
	void motorBackward(int pwm) { digitalWrite(forward_pin_, LOW); digitalWrite(backward_pin_, HIGH); analogWrite(PWM_pin_, pwm); }; 

public:
	CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
		int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr);
	// void initiate();
	void run(double expected_speed);
	void stop();
};

#endif