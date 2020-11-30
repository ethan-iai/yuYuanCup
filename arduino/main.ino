#include <arduino-timer.h>

#include <Sonar.h>

#include <Coder.h>
#include <CoderMotor.h>
#include <PID.h>

#include "header.h"
#include "pins.h"

// variables for coders to count pulses
volatile long left_front_count = 0;
volatile long right_front_count = 0;
volatile long left_back_count = 0;
volatile long right_back_count = 0;

// initiate all the hardWares and communication serial

// claim the coders and the motors
CoderMotor left_front_motor = CoderMotor(PWM_LEFT_FRONT, FORWARD_LEFT_FRONT , BACKWARD_LEFT_FRONT , CODER_VCC_LEFT_FRONT , CODER_A_LEFT_FRONT , CODER_B_LEFT_FRONT , &left_front_count);
CoderMotor right_front_motor = CoderMotor(PWM_RIGHT_FRONT, FORWARD_RIGHT_FRONT, BACKWARD_RIGHT_FRONT, CODER_VCC_RIGHT_FRONT, CODER_A_RIGHT_FRONT, CODER_B_RIGHT_FRONT, &right_front_count);
CoderMotor left_back_motor = CoderMotor(PWM_LEFT_BACK, FORWARD_LEFT_BACK, BACKWARD_LEFT_BACK, CODER_VCC_LEFT_BACK, CODER_A_LEFT_BACK, CODER_B_LEFT_BACK, &left_back_count);
CoderMotor right_back_motor = CoderMotor(PWM_RIGHT_BACK , FORWARD_RIGHT_BACK, BACKWARD_RIGHT_BACK , CODER_VCC_RIGHT_BACK, CODER_A_RIGHT_BACK, CODER_B_RIGHT_BACK, &right_back_count);

// claim the sonar
Sonar sonar = Sonar(SONAR_VCC_PIN, SONAR_TRIG_PIN, SONAR_ECHO_PIN);

// claim the timer
Timer<3, millis> timer;

// assitant function for interrupts
void positive(int negative_pin, volatile long* count_ptr) {
  if (digitalRead(negative_pin)) (*count_ptr)++;
  else (*count_ptr)--;
}

void negative(int positive_pin, volatile long* count_ptr) {
  if (digitalRead(positive_pin)) (*count_ptr)--;
  else (*count_ptr)++;
}

// the interrupts functions
void left_front_postive() {
  positive(CODER_B_LEFT_FRONT , &left_front_count);
};
void left_front_negative() {
  negative(CODER_A_LEFT_FRONT, &left_front_count);
};

void right_front_postive() {
  positive(CODER_B_RIGHT_FRONT , &right_front_count);
};
void right_front_negative() {
  negative(CODER_A_RIGHT_FRONT, &right_front_count);
};

void left_back_postive() {
  positive(CODER_B_LEFT_BACK , &left_back_count);
};
void left_back_negative() {
  negative(CODER_A_LEFT_BACK, &left_back_count);
};

void right_back_postive() {
  positive(CODER_B_RIGHT_BACK, &right_back_count);
};
void right_back_negative() {
  negative(CODER_A_RIGHT_BACK, &right_back_count);
};


void initIO() {
//	 Serial.begin(9600);

	// apply power to the coders
	digitalWrite(CODER_VCC_LEFT_FRONT, HIGH);
	digitalWrite(CODER_VCC_RIGHT_FRONT, HIGH);
	digitalWrite(CODER_VCC_LEFT_BACK, HIGH);
	digitalWrite(CODER_VCC_RIGHT_BACK, HIGH);

	// claim the delta_pixel input pin
	pinMode(ANALOG_READ_PIN, INPUT);
	pinMode(BACK_PIN, OUTPUT);
}

void attachInterrupts() {
	// attach interrupts function to the pins
	attachInterrupt(CODER_A_LEFT_FRONT, left_front_postive, RISING);
	attachInterrupt(CODER_B_LEFT_FRONT, left_front_negative, RISING);

	attachInterrupt(CODER_A_RIGHT_FRONT, right_front_postive, RISING);
	attachInterrupt(CODER_B_RIGHT_FRONT, right_front_negative, RISING);

	attachInterrupt(CODER_A_LEFT_BACK, left_back_postive, RISING);
	attachInterrupt(CODER_B_LEFT_BACK, left_back_negative, RISING);

	attachInterrupt(CODER_A_RIGHT_BACK, right_back_postive, RISING);
	attachInterrupt(CODER_B_RIGHT_BACK, right_back_negative, RISING);
}

unsigned long startTime = 0;

void setup() {
	initIO();
	attachInterrupts(); 

  	// set the timer that control motors every INTERVAL_MILLIS
	timer.every(INTERVAL_MILLIS, onTime);

  	// set the timer that switch the backward_period
 	timer.in(BACK_TIME_MILLIS / 2, changeBackwardPeriod);
  
  	// set the timer that drives the car home in BACK_TIME_MILLIS
	timer.in(BACK_TIME_MILLIS, backHome);
  
  	startTime = millis();
}

// read the delta_pixel from openMV 
int read() {
	return analogRead(ANALOG_READ_PIN) / 2 - 196;
}


// initiate the state as SPAWN, is_heading_home as false
int state = SPAWN;
bool is_heading_home = false;

int message = 0;
int backward_period = BACKWARD_PERIOD1;

void loop() {
	timer.tick();

	// if (is_heading_home == true && sonar.distanceCM() <= MIN_DISTANCE) return ;

	switch (state) {
		case FORWARD:
			message = read();
			if (message > OUT_OF_SIGHT || message < -OUT_OF_SIGHT) {
				// if lights off
				state = BACKWARD;
				startTime = millis();
			}
			break;
		case BACKWARD:
			if (millis() - startTime > backward_period || sonar.distanceCM() > MAX_BACKWARD_DISTANCE) { 
				// being backward for backward_period or moving farther than MAX_BACKWARD_DISTANCE
				// switch state to SPIN
				state = SPIN; 	
			}
			break;
		case SPIN:                                                                                                               
			message = read(); // message is either OUT_OF_SIGHT or the delta pixel
			if (message < FORWARD_PIXEL && message > -FORWARD_PIXEL) state = FORWARD;
			break;
    	case SPAWN:
			if (millis() - startTime > SPAWN_PERIOD) { state = SPIN; } 
			break;
		default: 
			// case STOP:
			message = read(); // message is either OUT_OF_SIGHT or the delta pixel
			if (message < FORWARD_PIXEL && message > -FORWARD_PIXEL) state = FORWARD;
			else state = SPIN;
			break;
	}
}

void setVelocity() {
	switch (state) {
		case FORWARD:
			set_forward_velocity(read(), sonar.distanceCM()); break;
		case BACKWARD:
			set_backward_velocity(); break;
		case SPIN:
			set_spin_velocity(); break;
  		case SPAWN:
  			set_forward_velocity(0, sonar.distanceCM()); break;
		default:
			set_stop_velocity(); break;
	}
}

bool onTime(void* ) {
	
	// onTime is called when time is up
	setVelocity();
	
	// 0 for left front wheel, 1 for right front wheel
	// 2 for right back wheel, 3 for left back wheel
	
	left_front_motor.run(speed_on_wheels[0]);
	right_front_motor.run(speed_on_wheels[1]);
	right_back_motor.run(speed_on_wheels[2]);
	left_back_motor.run(speed_on_wheels[3]);
	
	return true;
}

bool backHome(void* ) {
//  Serial.println("back home");
	is_heading_home = true;
	digitalWrite(BACK_PIN, HIGH);
	
	return false;
}

bool changeBackwardPeriod(void* ) {
  backward_period = BACKWARD_PERIOD2;
  return false;
} 
