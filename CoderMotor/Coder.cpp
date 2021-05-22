#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "Coder.h"

Coder::Coder() { }

Coder::Coder(int VCC_pin, int positive_pin, int negative_pin, volatile long *pulse_count_ptr) {
    pinMode(VCC_pin, OUTPUT);
    pinMode(positive_pin, INPUT);
    pinMode(negative_pin, INPUT);

    positive_pin_ = positive_pin;
    negative_pin_ = negative_pin; 
    pulse_count_ptr_ = pulse_count_ptr;
}

double Coder::getCurrentVelocity() {
	// Time elapsed after computing the velocity previously.
	// change in time is defined as previous - current to prevent round off error.
	unsigned long delta_time_millis = getChange(millis(), time_last_millis_); // in microseconds

    double current_velocity = VELOCITY_SCALE_VALUE * (double)(*pulse_count_ptr_) / delta_time_millis;

    *pulse_count_ptr_ = 0;
	time_last_millis_ = millis();
}
