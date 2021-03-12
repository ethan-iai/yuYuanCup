# YuyuanCup
## 1. Hardwares：
```cpp
class CoderMotor {
private:
	// ...
public:
	CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
		int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr) { }
	
	/**
	 * @param expected_speed scales from 0 to 100
	 */ 
	void run(double expected_speed);

	// stop the motor
	void stop();
};

class Sonar {
private:
	// ...
public:
    Sonar(int vccPin, int triggerPin, int echoPin);

    double distanceCM();

    /**
     * @param temperature temperature of environment
     */
    double distanceCM(float temperatur);  
};

```
## 2. arduino program
	run the controlling logic of the car 
	
## 3. openMV(camera): 
	output: the delta pixel between target and centre of camera

## Appendix：
    [小车底盘资料](http://www.7gp.cn/archives/195)
    [Mecanum轮及其速度分解计算](https://zhuanlan.zhihu.com/p/20282234?utm_source=qq&utm_medium=social)
    
