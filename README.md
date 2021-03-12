# YuyuanCup
## libs

- CoderMotor 

	wrap the motor with coder, API is provided as following: 

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
```

- Sonar

	wrap the sonar to measure the distance of front obstacle, API is provided as following: 

```cpp
class Sonar {
private:
	// ...
public:
    Sonar(int vccPin, int triggerPin, int echoPin);

    double distanceCM();

    /**
     * @param temperature temperature of environment
	 * to take the variation of sound speed into account
     */
    double distanceCM(float temperature);  
};

```
## arduino
*unorderedHandler* and *orderedHandler* are provided to control the car in 2 different stages of the game. 
	
## openMV 
detect the target, and transmit the parameters of target to arduino DUE board.

## Appendix：
[比赛规则](https://bhpan.buaa.edu.cn/#/link/7E5CFF6D305448837059D5E1C2D75403)
[小车底盘资料](http://www.7gp.cn/archives/195)
[Mecanum轮及其速度分解计算](https://zhuanlan.zhihu.com/p/20282234?utm_source=qq&utm_medium=social)
    
