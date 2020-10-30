#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "CoderMotor.h"

CoderMotor::CoderMotor(int PWM_pin, int forward_pin, int backward_pin, int coder_VCC_pin, 
    int coder_positive_pin, int coder_negative_pin, volatile long* pulse_count_ptr) {
    // initialize the motor pins
    // the PWM_pin must connect to the arduino digial pin with pwm-controlling
    // other pins connect to arduino digital pin
    pinMode(PWM_pin, OUTPUT);
    pinMode(forward_pin, OUTPUT);
    pinMode(backward_pin, OUTPUT);
    
    PWM_pin_ = PWM_pin;
    forward_pin_ = forward_pin;
    backward_pin_ = backward_pin;

    coder_ = Coder(coder_VCC_pin, coder_positive_pin, coder_negative_pin, pulse_count_ptr);
}
	
void CoderMotor::run(double expected_velocity) {
    double current_velocity = coder_.getCurrentVelocity();
    int pwm = get_PID_internal(current_velocity, expected_velocity);
    if (expected_velocity > 0) {
        motorForward(pwm);
    } else {
        motorBackward(pwm);
    }
    return ;
}

void CoderMotor::stop() {
    motorStop(0);
    return ;
}

