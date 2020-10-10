#include "arduino.h"

class Motor {
private:
        // motor_a and motor_b are two motor pins
		int motor_a;
		int motor_b;

        // coder_VCC and coder_GND are two coder pins that supply power
		int coder_VCC;
		int coder_GND;

        // coder_a and coder_n are two pins that supply the coder output
		int coder_a;
		int coder_b;

        void motorForward(int pwm) { do { analogWrite(motor_a, pwm); analogWrite(motor_b, 0); } while (false) }; 
		void motorStop(int pwm) { do { analogWrite(motor_a, 0); analogWrite(motor_b, 0); } while (false) }; 
		void motorBackward(int pwm) { do { analogWrite(motor_a, 0); analogWrite(motor_b, pwm); } while (false) } 
		
public:
        void run(double expected_speed) {
            
        }

        double getCurrentSpeed() {
            
        }	
};