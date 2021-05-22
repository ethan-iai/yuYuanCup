#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PID.h"

class PIDController {
private:
    /* data */
    float error[5] = {0};
    float de = 0;

    int pwm_old = 0;
    int pwm_cur = 0;
public:
    PIDController();
    int get_PID_internal(double expected_speed, double cur_speed);
};

#endif