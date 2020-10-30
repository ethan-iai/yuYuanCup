#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PID.h"

int get_PID_internal(double expected_speed, double cur_speed) {
	pwm_old = (cur_speed - MIN_SPEED) / (MAX_SPEED - MIN_SPEED) * (MAX_PWM - MIN_PWM) + MIN_PWM;

	for(int i = 0; i < 3; i++) {
		error[i] = error[i + 1];
	}
	error[3] = expected_speed - cur_speed;	

	de = kp_motor * (error[3] - error[2]) + ki_motor * error[3] - kd_motor * (error[3] - 2 * error[2] + error[1]);
	pwm_cur = pwm_old + de;
  	if (pwm_cur > MAX_PWM) {
		pwm_cur = MAX_PWM;
	} else if (pwm_cur < MIN_PWM) {
		pwm_cur = MIN_PWM;
	}
	
  	cur_speed = expected_speed;
  	pwm_old = pwm_cur; 
  	return pwm_cur; //输出PWM波
}

void get_speed_on_wheels(int decision_coefficient, int direction_coefficient, int distance_coefficient) {
    switch (decision_coefficient) {
        case 1:
            speed_on_wheels[0] = speed_on_wheels[3] = MAX_SPEED * distance_coefficient;
            speed_on_wheels[1] = speed_on_wheels[2] = MAX_SPEED * direction_coefficient * distance_coefficient;
            break;
        case 2:
            speed_on_wheels[1] = spped_on_wheels[2] = MAX_SPEED * distance_coefficient;
            speed_on_wheels[0] = speed_on_wheels[3] = MAX_SPEED * direction_coefficient * distance_coefficient;
            break;
        default:
            for (int i = 0; i < 4; ++i) { 
                speed_on_wheels[i] = MAX_SPEED * distance_coefficient;
            }
            break;
    }
    return ;
}

void get_expected_velocity(int expected_pixel, double length) {
    int distance_coefficient = (length >= DECELERATION_DISTANCE) ? (1) : (length / DECELERATION_DISTANCE);
    int direction_coefficient = 1 - abs(expected_pixel) * corresponding_angle / 45;
    int decision_coefficient = 0;
    
    if (expected_pixel > THRESHOLD) {
        // turn right 
        decision_coefficient = 1;
    } else if (expected_pixel < -THRESHOLD) { 
        // turn left
        decision_coefficient = 2; 
    }
            
    get_speed_on_wheels(decision_coefficient, direction_coefficient, distance_coefficient);
    return ;
}
