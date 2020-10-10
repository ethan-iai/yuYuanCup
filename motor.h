#ifdef motor
#define motor

class Motor {
private:
		int motor_a;
		int motor_b;

		int coder_VCC;
		int coder_GND;

		int coder_a;
		int coder_b;

        void motorForward(int pwm) { do { analogWrite(motor_a, pwm); analogWrite(motor_b, 0); } while (false) } 
		void motorStop(int pwm) { do { analogWrite(motor_a, 0); analogWrite(motor_b, 0); } while (false) } 
		void motorBackward(int pwm) { do { analogWrite(motor_a, 0); analogWrite(motor_b, pwm); } while (false) } 
		
public:
        void run(double expected_speed);
        double getCurSpeed();	
}

#endif