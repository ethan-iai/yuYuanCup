# CoderMotor 

## features
- lib for motor with encoder  
- simple algorithm inside (can be overrided)

## API
```cpp
/**
 * declare a CoderMotor in arduino program
 */ 
volatile long count = 0;    // definate encoder increment varaible 
CoderMotor(PWM_PIN, FORWARD_PIN, BACKWARD_PIN, CODER_VCC_PIN, 
           CODER_POSITIVE_PIN, CODER_NEGATIVE_PIN, &count) aCoderMotor;

/**
 * control the motor to run at given velocity 
 * scale from [0, 100] (with mapping to pwm {0, 255})
 * this function will call a pid algorithm to control 
 * the velocity precisly 
*/
aCoder.run(EXPECTITED_VELOCITY);
```
### advanced 
To let the lib to fit different encoder-motors, you can modify the parameters in `PID.h` . 
    
