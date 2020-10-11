# 驭远杯
## 1. motor and encoder control program：
	input: double cur_speed, double expected_speed  
	call : getPIDInternal()， attachInterrupt()
	output: directly control the motor
```cpp
class Motor {
private:
		// motor_a and motor_b are two motor pins
		int motor_a;
		int motor_b;

		// coder_VCC and coder_GND are two coder pins that supply power
		// the coder_GND pin (coder_GND_) connect the the GND of arduino 
		int coder_VCC_;

		// coder_a and coder_n are two pins that supply the coder output
		int coder_a;
		int coder_b;

		int forward_; 

		void motorForward(int pwm) { }; 
		void motorStop(int pwm) { }; 
		void motorBackward(int pwm) { }; 
		void coderA() { };
		void coderB() { };	

public:
		// 根据期望速度与实际速度调用PID产生PWM信号
		void run(double expected_speed) {
			double cur_speed = getCurSpeed();
			expected_pwm = get_PID_internal(expected_speed, cur_speed);
			// 设置电机引脚高低电平与PWM控制电机运转
		}

		// 得到当前电机对应速度，通过编码器的输出计算
		double getCurrentSpeed() { return cur_speed; }	
}

```
## 2. arduino program
    input:  expected_speed_A, expected_speed_B, expected_speed_C, expected_speed_D// 目标距离与像素差
    output: ...
```cpp
	// 从openMV与arduino的通信串口中获得四轮目标速度
	
	void read() { } // 读取四轮期望速度
	
	// 初始化各串口
	void initIO() {
		Serial.begin(19200);	
	} 
	
	void setup() {
		MsTimer2::set(interval, onTime); //定时器绑定, interval为间隔时间，onTime为定时执行速度控制程序
  		initIO(); // 串口初始化
		
		//中断引脚绑定
		attachInterrupt(digitalPinToInterrupt(CO1A), coder_1_A, rising);

		//定时器开始
		MsTimer2::start();
	}
	
	void loop() {
		// 读取并处理串口数据
		read();
		
		// ...
	}
	
	void onTime() {
		// 定时器响，进入onTime函数
		motorA.run(expected_speed_A);
		motorB.run(expected_speed_B);
		motorC.run(expected_speed_D);
		motorD.run(expected_speed_D);
	}
	
	void rising() { }
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
    
