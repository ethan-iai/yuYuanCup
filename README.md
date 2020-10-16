# 驭远杯
## 1. motor and encoder control program：
	input: double cur_speed, double expected_speed  
	call : getPIDInternal()， attachInterrupt()
	output: directly control the motor
```cpp
class CoderMotor {
private:
	// motor_a and motor_b are two motor pins
	int PWM_pin_; // PWM output pin
	int forward_pin_; // if high, motor runs forward
	int backward_pin_;

	Coder coder_; //  coder of the motor 

	void motorForward(int pwm) { }
	void motorStop(int pwm) { }
	void motorBackward(int pwm) { } 

public:
	CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
		int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr) { }
	
	// 根据期望速度与实际速度调用PID产生PWM信号
	void run(double expected_speed) {
		// ...
		pwm = get_PID_internal(expected_speed, cur_speed);
		// 设置电机引脚高低电平与PWM控制电机运转
		// ...
	}
	void stop() { }
};

class Coder {
private:
    // coder_VCC and coder_GND are two coder pins that supply power
	// the coder_GND pin (coder_GND_) connect the the GND of arduino 
	int VCC_pin_;
	
	// positive_pin and negative_pin are two pins that supply the coder output
	int positive_pin_;
	int negative_pin_;

	// pulseCount record the number of pulses during the interval from last_time_us_ to cur_time_us_
	// if pulse_count > 0, the motor is running forward 
	// else, the motor move backwards
	volatile long *pulse_count_ptr_;

	// intialize time_last_micros_ to 0
	unsigned long time_last_micros_;

    unsigned long static Coder::getChange(long current, long previous) { }

public:
    Coder();
    Coder(int VCC_pin, int positive_pin, int negative_pin, volatile long *pulse_count_ptr);
    double getCurrentVelocity();
}

```
## 2. arduino program
    input:  expected_speed_A, expected_speed_B, expected_speed_C, expected_speed_D// 目标距离与像素差
    output: ...
```cpp
	// 从openMV与arduino的通信串口中获得四轮目标速度
	
	void read() { } // 读取四轮期望速度
	
	// 初始化各串口
	void initIO() 
	{
		Serial.begin(19200);
		// for every pin
			pinMode(pin, mode);	
	} 
	
	void onTime() {
		// 定时器响，进入onTime函数
		motorA.run(expected_speed_A);
		motorB.run(expected_speed_B);
		motorC.run(expected_speed_D);
		motorD.run(expected_speed_D);
	}
	
		
	void attachInterrupts()
	{   
		// for every coder 
			// every coder has positive_pin and negative_pin
			attachInterrupt(positive_pin, ..._..._positive, RISING);
			attachInterrupt(negative_pin, ..._..._negative, RISING);
	}

	void setup() 
	{
		MsTimer2::set(interval, onTime); //定时器绑定, interval为间隔时间，onTime为定时执行速度控制程序
  		initIO(); // 串口初始化
		
		
		// 定时器开始
		MsTimer2::start();
	}
	
	void loop() {
		// 读取并处理串口数据
		read();
		
		// ...
	}
	
```

## 3. sensing(sonar & camera): 
	input: mode
    	output：length, delta of pixel blocks
```python
# sensing 
# 从串口中读取mode信息

	length = 0;
	delta_pixel = 0;
	
	def distanceMeasurement(length):
		# ...
		length = read1
	
	def visualIdentity(delta_pixel):
		# ...
		delta_pixel = read2
	
	# 传感器初始化、参数调整
	# ...
	
	while (True):
		# takePhoto
		distanceMeasurement(length)
		visualIdentity(delta_pixel)
		# 串口中传出json信息
```

## 4. PID alogorithm
### PID_external
	input: length, delta of pixel blocks
	output: expected_speed_A, expected_speed_B, expected_speed_C, expected_speed_D
```python
	def get_pid_external(self, error) 
		# ...
		return expected_speed
```
### PID_internal
	input: expected_speed, cur_speed
	output: expected_pwm
```cpp
	int get_pid_internal(double expected_speed, double cur_speed) {
		// ...
		return expected_pwm;
	}
```
## 附录：
    规则网页：https://mp.weixin.qq.com/s/D6dDW7oGuLzhpgyk5TNQ_A
    小车底盘资料：http://www.7gp.cn/archives/195
	Mecanum轮及其速度分解计算：https://zhuanlan.zhihu.com/p/20282234?utm_source=qq&utm_medium=social
    
