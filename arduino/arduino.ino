#include <CoderMotor.h>

#include <SoftwareSerial.h>
#include "MsTimer2.h"  

SoftwareSerial softSerial(10,11); //定义软串口,rx为10号端口,tx为11号端口

typedef struct
{
  int data[50][4] = {{0,0,0,0}};
  int len = 0;
}List;
List list;

volatile long A_count = 0;
volatile long B_count = 0;
volatile long C_count = 0;
volatile long D_count = 0;

double expected_speed_A;
double expected_speed_B;
double expected_speed_C;
double expected_speed_D;

void initIO()
{
    Serial.begin(19200);
    softSerial.begin(9600); //初始化虚拟串口
 // pinMode(CO1A, INPUT_PULLUP);//引脚配置为输入
}

void setup()
{
  MsTimer2::set(25, OnTime); //定时器绑定
  initIO();
  // 电机初始化
  // CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr);
 // CoderMotor  motorA = CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
  //  int coder_a_pin, int coder_b_pin, A_count) 
  
   // CoderMotor  motorB = CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
  //  int coder_a_pin, int coder_b_pin, B_count) 
  
   // CoderMotor  motorC = CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
  //  int coder_a_pin, int coder_b_pin, C_count) 
  
   // CoderMotor  motorD = CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, 
  //  int coder_a_pin, int coder_b_pin, D_count) 
  
  //中断引脚绑定
 // attachInterrupt(digitalPinToInterrupt(CO1A), coder_1_A, read);
   MsTimer2::start();//定时器开始
}
String A_String = "";//定义用来存数据的字符串

void read(){ // 读取四轮期望速度
  if(softSerial.available())
  {
    getList();
    
      expected_speed_A=list.data[1][0];
      expected_speed_B=list.data[1][1];
      expected_speed_D=list.data[1][2];
      expected_speed_D=list.data[1][3];

    clearList();
  }
} 

void loop()
{
    // 读取并处理串口数据
    read();
    
}
  
void OnTime()
{
// 定时器响，进入onTime函数
//    motorA.run(expected_speed_A);
//    motorB.run(expected_speed_B);
//    motorC.run(expected_speed_C);
//    motorD.run(expected_speed_D);
}
  

String detectString()
{
  while (softSerial.read() != '{');
  return (softSerial.readStringUntil('}'));
}

void clearList()
{
  memset(list.data, sizeof(list.data),0);
  list.len = 0;
}

void getList()
{
  String s = detectString();
  String numStr = "";
  for (int i = 0; i < s.length(); i++)
  {
    if(s[i] == '(')
    {
      numStr = "";
    }
    else if (s[i] == ',')
    {
      list.data[list.len][0] = numStr.toDouble();
      numStr = "";
    }
    else if(s[i] == ':')
    {
      list.data[list.len][1] = numStr.toDouble();
      numStr = "";
    }
    else if(s[i] == ';')
    {
      list.data[list.len][2] = numStr.toDouble();
      numStr = "";
    }
    else if(s[i]==')')
    {
      list.data[list.len][3] = numStr.toDouble();
      numStr = "";
      list.len++;
    }
    else
    {
      numStr += s[i];
    }
  }
}
