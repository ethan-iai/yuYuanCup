#ifndef MOTOR_H_
#define MOTOR_H_

// include "myArduino" in experimental environment to replace the arduino lib

#include "myArduino.h"

class Motor {
private:
	// the ratio of speed and impulse interval
	static constexpr double MODULUS = 76923.077;

	// motor_a and motor_b are two motor pins
	int motor_a_;
	int motor_b_;

	// coder_VCC and coder_GND are two coder pins that supply power
	// the coder_GND pin (coder_GND_) connect the the GND of arduino 
	int coder_VCC_;
	
	// coder_a and coder_n are two pins that supply the coder output
	int coder_a_;
	int coder_b_;

	// pulseCount record the number of pulses during the interval from last_time_us_ to cur_time_us_
	// if pulse_count > 0, the motor is running forward 
	// else, the motor move backwards
	int pulse_count_; 

	// intialize cur_time_us_ and last_time_us_ to 0
	unsigned long cur_time_us_;
	unsigned long last_time_us_;

	void motorForward(int pwm) { do { analogWrite(motor_a_, pwm); analogWrite(motor_b_, 0); } while (false); }; 
	void motorStop(int pwm) { do { analogWrite(motor_a_, 0); analogWrite(motor_b_, 0); } while (false); }; 
	void motorBackward(int pwm) { do { analogWrite(motor_a_, 0); analogWrite(motor_b_, pwm); } while (false); }; 
	void coderA() { if (digitalRead(coder_a_)) pulse_count_++; else pulse_count_--; };
	void coderB() { if (digitalRead(coder_b_)) pulse_count_--; else pulse_count_++; };	
	
public:
	Motor(int motor_a, int motor_b, int coder_VCC, int coder_a, int coder_b);
	void initiate();
	void run(double expected_speed);
	void stop();
	double getCurrentSpeed();	
};

#endif