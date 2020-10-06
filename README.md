# 驭远杯
## 1. motor and encoder control：
	input: double cur_speed, double expected_speed  
	call : PID
	output: directly control the motor
```cpp
class Motor {
	private:
		int dir1;
		int dir2;
		int pwm;
		int coder1;
		int coder2;
	public:
		// 根据期望速度与实际速度调用PID产生PWM信号
		void run(double cur_speed, double expected_speed) { }

		// 得到当前电机对应速度，通过编码器的输出计算
		double get_speed() { return cur_speed;}	
} 

class Drive {
	private: 
		Motor motorA;
		Motor motorB;
		Motor motorC;
		Motor motorD;
	public:
		void rotate_counter_clockwise() { }
		void rotate_clockwise() { }
		void engage_target() { }
}
```
## 2. control
    input: mode, target_distance, delta_pixel // 目标距离与像素差
    output: take different action mode
```cpp
	// 从openMV与arduino的通信串口中字符串
	int mode;
	double target_distance;
	int delta_pixel;
	
	void read() { }
	void setup() {
		init_IO();		
	}

	void loop() {
		decode;
		switch (mode) {
			case 0:
				// 旋转寻找目标
				break;
			case 1:
				// 找到目标，冲刺
				break;
			case 2:
				// 完成碰撞，后退
				break;
			case 3:
				// 劫掠
				break;
			default:
				break;
		}
	}
```

## sensing(sonar & camera): 
	input: ... 
    output：...
```python
// sensing 
```


## 附录：
    规则网页：https://mp.weixin.qq.com/s/D6dDW7oGuLzhpgyk5TNQ_A
    小车底盘资料：http://www.7gp.cn/archives/195
    所需学习资料在git的word文档中
