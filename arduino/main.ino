#include "CoderMotor.h"

#include <SoftwareSerial.h>
#include <MsTimer2.h>  

SoftwareSerial softSerial(10,11); //定义软串口,rx为10号端口,tx为11号端口
int openmv_data[3];//openmv通讯

//具体引脚待确定
int PWM_left_front ;
int foward_left_front;
int backward_left_front;
int coder_Vcc_left_front;
int coder_a_left_front;
int coder_b_left_front;

int PWM_right_front;
int foward_right_front;
int backward_right_front;
int coder_Vcc_right_front;
int coder_a_right_front;
int coder_b_right_front;

int PWM_left_back;
int foward_left_back;  
int backward_left_back; 
int coder_Vcc_left_back;
int coder_a_left_back;  
int coder_b_left_back;  

int PWM_right_back;
int foward_right_back;
int backward_right_back;
int coder_Vcc_right_back; 
int coder_a_right_back; 
int coder_b_right_back;

volatile long left_front_count = 0;
volatile long right_front_count = 0;
volatile long left_back_count = 0;
volatile long right_back_count = 0;

int expected_speed_left_front = 0;
int expected_speed_right_front = 0;
int expected_speed_left_back = 0;
int expected_speed_right_back = 0;

// call the constructor of CoderMotor class
// CoderMotor(int PWM_pin, int forward_pin, int backward_pin_, int coder_VCC_pin, int coder_a_pin, int coder_b_pin, volatile long* pulse_count_ptr);
CoderMotor left_front_motor  = CoderMotor(PWM_left_front ,foward_left_front ,backward_left_front ,coder_Vcc_left_front ,coder_a_left_front ,coder_b_left_front , &left_front_count);
CoderMotor right_front_motor = CoderMotor(PWM_right_front,foward_right_front,backward_right_front,coder_Vcc_right_front,coder_a_right_front,coder_b_right_front, &right_front_count);
CoderMotor left_back_motor   = CoderMotor(PWM_left_back  ,foward_left_back  ,backward_left_back  ,coder_Vcc_left_back  ,coder_a_left_back  ,coder_b_left_back  , &left_back_count);
CoderMotor right_back_motor  = CoderMotor(PWM_right_back ,foward_right_back ,backward_right_back ,coder_Vcc_right_back ,coder_a_right_back ,coder_b_right_back , &right_back_count);

// call the positive() and negative() listed below
// if the positive pin of the left front coder connects to arduino no.10 pin
// call left_front_positive { postive(10, &left_front_count)};  
void left_front_postive() { positive(coder_a_left_front , &left_front_count); };
void left_front_negative() { negative(coder_b_left_front, &left_front_count); };

void right_front_postive() { positive(coder_a_right_front , &right_front_count); }; 
void right_front_negative() { negative(coder_b_right_front, &right_front_count); };

void left_back_postive() { positive(coder_a_left_back , &left_back_count); };
void left_back_negative() { negative(coder_b_left_back, &left_back_count); };

void right_back_postive() { positive(coder_a_right_back , &right_back_count); };
void right_back_negative() { negative(coder_b_right_back, &right_back_count); };

void positive(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)++;
    else (*count_ptr)--;
}

void negative(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)--;
    else (*count_ptr)++;
}

void initIO()
{   
    Serial.begin(19200);
    softSerial.begin(19200); //初始化虚拟串口
    // initiate the IO pins
}

void attachInterrupts()//??不明白要干什么
{   
//    // for every coder 
//    // every coder has positive_pin and negative_pin
//        attachInterrupt(positive_pin, left_front_postive, RISING);
//        attachInterrupt(negative_pin, left_front_negative, RISING);

//        attachInterrupt(positive_pin, right_front_postive, RISING);
//        attachInterrupt(negative_pin, right_front_negative, RISING);

//        attachInterrupt(positive_pin, left_back_postive, RISING);
//        attachInterrupt(negative_pin, left_back_negative, RISING);

//        attachInterrupt(positive_pin, right_back_postive, RISING);
//        attachInterrupt(negative_pin, right_back_negative, RISING);
}

void setup()
{
    MsTimer2::set(25, OnTime); //定时器绑定
    initIO();   
    attachInterrupts();
    MsTimer2::start();//定时器开始
}


void loop()
{
    read(); 
}

void OnTime()
{   // 定时器响，进入onTime函数
    left_front_motor.run(expected_speed_left_front);
    right_front_motor.run(expected_speed_right_front);
    left_back_motor.run(expected_speed_left_back);
    right_back_motor.run(expected_speed_right_back);
}

void read()
{ // 读取四轮期望速度
  if(softSerial.available())
  {
    getList();
    expected_speed_left_front = openmv_data[0];
    expected_speed_right_front = openmv_data[1];
    expected_speed_left_back = openmv_data[1];
    expected_speed_right_back = openmv_data[0];
      Serial.print(openmv_data[0]);
      Serial.print('\t');
      Serial.println(openmv_data[1]);

    clearList();
  }
}

//openmv通讯
String detectString()
{
  while(softSerial.read() != '(');
  return(softSerial.readStringUntil(')'));
}
void clearList()
{
  memset(openmv_data, sizeof(openmv_data),0);
}
void getList()
{
  String s = detectString();
  String numStr = "";
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i]=='(') 
    {
      numStr = "";
    }
    else if (s[i] == ',')
    {
      openmv_data[0] = numStr.toInt();
      numStr = "";
    }
    else if (s[i] == ')')
    {
      openmv_data[1] = numStr.toInt();
      numStr = "";
    }
    else
    {
      numStr += s[i];
    }
  }
}
