#ifndef HEADER_H_
#define HEADER_H_

#define INTERVAL_MILLIS (25)

#ifdef DBG
  #define BACK_TIME_MILLIS (60000)
#else 
  #define BACK_TIME_MILLIS (360000)
  #define NDEBUG
#endif

#define MOVE_PAN_LEFT_PERIOD (800)
#define MOVE_PAN_RIGHT_PERIOD (800)
#define BACKWARD_PERIOD (700) 

#define SPAWN (0)
#define FORWARD (1)
#define BACKWARD (2)
#define SPIN (3)
#define COLLECTING (4)
#define RESET (5)

#define OUT_OF_SIGHT (140)

extern int speed_on_wheels[4];


#endif
