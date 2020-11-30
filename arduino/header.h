#ifndef HEADER_H_
#define HEADER_H_

#define INTERVAL_MILLIS (25)

#ifdef DBG
  #define BACK_TIME_MILLIS (60000)
#else 
  #define BACK_TIME_MILLIS (360000)
#endif

#define SPAWN_PERIOD (2500)
#define BACKWARD_PERIOD1 (1200)
#define BACKWARD_PERIOD2 (700) 

#define SPAWN (0)
#define FORWARD (1)
#define BACKWARD (2)
#define SPIN (3)

#define OUT_OF_SIGHT (180)

extern int speed_on_wheels[4];


#endif
