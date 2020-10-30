#ifndef PID_H_
#define PID_H_

// parameters table provided to modify 
#define max_pwm 250
#define mid_pwm 125
#define min_pwm 0
#define max_speed 100
#define min_speed 0

static float error[10];

int get_PID_internal(double expected_speed, double cur_speed);

#endif