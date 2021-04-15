#ifndef HEADER_H_
#define HEADER_H_

#include <arduino-timer.h>

#include <Sonar.h>

#include <Coder.h>
#include <CoderMotor.h>
#include <PID.h>

#define INTERVAL_MILLIS (25)

#ifdef DBG
  #define BACK_TIME_MILLIS (60000)
#else 
  #define BACK_TIME_MILLIS (360000)
  #define NDEBUG
#endif

#define SPAWN_PERIOD (2500)

#define FORWARD_PIXEL (90)
#define OUT_OF_SIGHT (140)

#define BACKWARD_PERIOD (700) 
#define MAX_BACKWARD_DISTANCE (80)

#define SPAWN (0)
#define FORWARD (1)
#define BACKWARD (2)
#define SPIN (3)


extern int speed_on_wheels[4];


#endif
