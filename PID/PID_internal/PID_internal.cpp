#include "PID.h"

int get_PID_internal(double expected_speed, double cur_speed) {
	pwm_old = (cur_speed - min_speed) / (max_speed - min_speed) * (max_pwm - min_pwm) + min_pwm;

	for(int i = 0; i < 3; i++) {
		error[i] = error[i + 1];
	}
	error[3] = expected_speed - cur_speed;	

	de = kp_motor * (error[3] - error[2]) + ki_motor * error[3] - kd_motor * (error[3] - 2 * error[2] + error[1]);
	pwm_cur = pwm_old + de;
  	if (pwm_cur > max_pwm) {
		pwm_cur = max_pwm;
	} else if (pwm_cur < min_pwm) {
		pwm_cur = min_pwm;
	}
	
  	cur_speed = expected_speed;
  	pwm_old = pwm_cur; 
  	return pwm_cur; //输出PWM波
}
