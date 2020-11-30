#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PIDController.h"

PIDController::PIDController() { }

int PIDController::get_PID_internal(double expected_speed, double cur_speed) {
    expected_speed = (expected_speed > 0)? expected_speed : -expected_speed;
    cur_speed = (cur_speed > 0)? cur_speed : -cur_speed;

    pwm_old = (cur_speed - MIN_SPEED) / (MAX_SPEED - MIN_SPEED) * (MAX_PWM - MIN_PWM) + MIN_PWM;
   
    for(int i = 0; i < 3; i++) {
        error[i] = error[i + 1];
    }
    // error3 need to abs?
    error[3] = expected_speed - cur_speed;	

    de = kp_motor * (error[3] - error[2]) 
        + ki_motor * error[3] 
        - kd_motor * (error[3] - 2 * error[2] + error[1]);
    pwm_cur = pwm_old + de;
    
    if (pwm_cur > MAX_PWM) {
        pwm_cur = MAX_PWM;
    } else if (pwm_cur < MIN_PWM) {
        pwm_cur = MIN_PWM;
    }
    
    return pwm_cur; //输出PWM波
}