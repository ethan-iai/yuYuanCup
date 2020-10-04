# 驭远杯
## 模块一 运动：
    输入：控制指令，红外传感器信息 
    输出：行动状态指令
```cpp
    int code_fl[];
    int code_fr[];
    int code_bl[];
    int code_br[];
    // f&b指front&back，l&r指left&right，code_fl指传给左前轮编码器的代码
    
    // drive()函数直接写四个编码数组来实现对小车的控制
    // state = 2 时小车前进， state = 1时小车后退，state = 0 小车静止，state = -1小车旋转 
    // command为控制模块输出的指令
    // 小车前后左右有四个红外线传感器，若感应到线sensor = 1, 反之sensor = 0
    int drive(const int command[], int sensor_f, int sensor_l, int sensor_r, int sensor_b) { return state; }
```
## 模块二 控制：
    输入：环境讯息（感知，循迹，碰撞） 
    输出：行动状态指令
```cpp
    // command[]为一个各位包含小车运动参数的数组，随自由度而拓展
    int[] control(const int lightMSG[], const int position[], const int touched, ...) { return command; }
```
## 模块三 感知：
    输入：摄像头信息（从硬件接口得到）
    输出：画面是否有灯光（bool）， 颜色（bool）
```cpp
    // lightMSG[0] 存储该帧图像中是否存在灯光
    // lightMSG[1] 存储该帧图像中的灯光信息，若灯为绿lightMSG[1] = 1，若灯为红lightMSG[1] = 0
    int[] getLightInSight(Type pictureMSG) { return lightMSG; }
```
## 模块四 碰撞：
    输入：碰撞信息（从硬件接口中得到）
    输出：有无碰撞
```cpp
    // 如果touched为真（1），则小车与灯塔已达到碰撞状态
    int isTouched(const Type clashMSG) { return touched; }
```
## 附录：
    规则网页：https://mp.weixin.qq.com/s/D6dDW7oGuLzhpgyk5TNQ_A
    小车底盘资料：http://www.7gp.cn/archives/195
    所需学习资料在word文档中
