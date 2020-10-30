#include "CoderMotor.h"

#include <SoftwareSerial.h>
#include <MsTimer2.h>  

int openmv_data[3];//openmv通讯

//具体引脚待确定
// change all the variables to marco 
// please

#define PWM_LEFT_FRONT 
#define FOWARD_LEFT_FRONT
#define BACKWARD_LEFT_FRONT
#define CODER_VCC_LEFT_FRONT
#define CODER_A_LEFT_FRONT
#define CODER_B_LEFT_FRONT

#define PWM_RIGHT_FRONT
#define FOWARD_RIGHT_FRONT
#define BACKWARD_RIGHT_FRONT
#define CODER_VCC_RIGHT_FRONT
#define CODER_A_RIGHT_FRONT
#define CODER_B_RIGHT_FRONT

#define PWM_LEFT_BACK
#define FOWARD_LEFT_BACK  
#define BACKWARD_LEFT_BACK 
#define CODER_VCC_LEFT_BACK
#define CODER_A_LEFT_BACK  
#define CODER_B_LEFT_BACK  

#define PWM_RIGHT_BACK
#define FOWARD_RIGHT_BACK
#define BACKWARD_RIGHT_BACK
#define CODER_VCC_RIGHT_BACK 
#define CODER_A_RIGHT_BACK
#define CODER_B_RIGHT_BACK

#define SONAR_VCC_PIN
#define SONAR_TRIG_PIN
#define SONAR_ECHO_PIN

#define MIN_LENGTH (5)

volatile long left_front_count = 0;
volatile long right_front_count = 0;
volatile long left_back_count = 0;
volatile long right_back_count = 0;

// have already claim speed_on_wheels[] in PID.h
// directly call speed_on_wheels[] 

// initiate all the hardWares and communication serial 

// claim the software serial
SoftwareSerial softSerial(10,11); //定义软串口,rx为10号端口,tx为11号端口

CoderMotor left_front_motor = CoderMotor(PWM_LEFT_FRONT, FOWARD_LEFT_FRONT ,BACKWARD_LEFT_FRONT ,CODER_VCC_LEFT_FRONT ,CODER_A_LEFT_FRONT ,CODER_B_LEFT_FRONT , &left_front_count);
CoderMotor right_front_motor = CoderMotor(PWM_RIGHT_FRONT, FOWARD_RIGHT_FRONT, BACKWARD_RIGHT_FRONT, CODER_VCC_RIGHT_FRONT, CODER_A_RIGHT_FRONT, CODER_A_RIGHT_FRONT, &right_front_count);
CoderMotor left_back_motor = CoderMotor(PWM_LEFT_BACK, FOWARD_LEFT_BACK, BACKWARD_LEFT_BACK, CODER_VCC_LEFT_BACK, CODER_A_LEFT_BACK, CODER_B_LEFT_BACK, &left_back_count);
CoderMotor right_back_motor = CoderMotor((PWM_RIGHT_BACK ,FOWARD_RIGHT_BACK, BACKWARD_RIGHT_BACK ,CODER_VCC_RIGHT_BACK, CODER_A_RIGHT_BACK, CODER_B_RIGHT_BACK, &right_back_count);

Sonar sonar = Sonar(SONAR_VCC_PIN, SONAR_TRIG_PIN, SONAR_ECHO_PIN);

// call by the interrupts 
void positive(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)++;
    else (*count_ptr)--;
}

void negative(int pin, volatile long *count_ptr) {
    if (digitalRead(pin)) (*count_ptr)--;
    else (*count_ptr)++;
}

// call the positive() and negative() listed below
// if the positive pin of the left front coder connects to arduino no.10 pin
// call left_front_positive { postive(10, &left_front_count)};  
void left_front_postive() { positive(CODER_A_LEFT_FRONT , &left_front_count); };
void left_front_negative() { negative(CODER_B_LEFT_FRONT, &left_front_count); };

void right_front_postive() { positive(CODER_A_RIGHT_FRONT , &right_front_count); }; 
void right_front_negative() { negative(CODER_B_RIGHT_FRONT, &right_front_count); };

void left_back_postive() { positive(CODER_A_LEFT_BACK , &left_back_count); };
void left_back_negative() { negative(CODER_B_LEFT_BACK, &left_back_count); };

void right_back_postive() { positive(CODER_A_RIGHT_BACK, &right_back_count); };
void right_back_negative() { negative(CODER_B_RIGHT_BACK, &right_back_count); };

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

void loop(){
  int message = get_message_from_openmv();
  double distance = sonar.distanceCM();

  if (collision_finished == true && is_heading_to_home == true) return;
  else if (collision_finished == true && is_heading_to_home == false) 
  {
      // set the expected speed so the car will move backward
      // control car to move backward
      //连续运行control_car_to_back_off一段时间?
      // hint: distance?
  }

  switch(message) {
      case 1001:
          // control car to spin
          break;
      case 1002:
          is_heading_to_home = 1;
          // set the expected speed to control the car to spin
          // control car to spin();
          break;
      default:
          get_expected_velocity(mesasge, distance);
          break;
  }
}

void OnTime()
{   // 定时器响，进入onTime函数
    left_front_motor.run(speed_on_wheels[0]);
    right_front_motor.run(speed_on_wheels[1]);
    left_back_motor.run(speed_on_wheels[2]);
    right_back_motor.run(speed_on_wheels[3]);
}

void read()
{ // 读取四轮期望速度
  if(softSerial.available())
  {
    getList();
    speed_on_wheels[0] = openmv_data[0];
    speed_on_wheels[1] = openmv_data[1];
    speed_on_wheels[2] = openmv_data[1];
    speed_on_wheels[3] = openmv_data[0];
      
    // Serial.print(openmv_data[0]);
    // Serial.print('\t');
    // Serial.println(openmv_data[1]);

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
