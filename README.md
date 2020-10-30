# 驭远杯
## 1. Hardwares：
```cpp
class CoderMotor {
private:
	// ...
public:
	CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
		int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr) { }
	
	void run(double expected_speed);
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
    input:  expected_speed_A, expected_speed_B, expected_speed_C, expected_speed_D// or 目标距离与像素差
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
	output:
	the delta pixel between target and centre of camera

## 4. PID 
### PID_external
	input: detected delta of pixel
	output: refined delta of pixel

### PID
```cpp
	// the expected speed for four wheels
	// 0 for left front wheel, 1 for right front wheel
	// 2 for right rear wheel, 3 for left rear wheel
	static int speed_on_wheels[4];  

	// get the refined pwm to control the motor
	int get_PID_internal(double expected_speed, double cur_speed);

	// compute the expected speed of four wheels
	// store them in the array: speed_on_wheels[]
	void get_expected_velocity(int expected_pixel, double length);

```
## 附录：
    规则网页：https://mp.weixin.qq.com/s/D6dDW7oGuLzhpgyk5TNQ_A
    小车底盘资料：http://www.7gp.cn/archives/195
	Mecanum轮及其速度分解计算：https://zhuanlan.zhihu.com/p/20282234?utm_source=qq&utm_medium=social
    
