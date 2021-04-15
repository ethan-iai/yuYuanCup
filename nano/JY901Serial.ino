
#include <Wire.h>
#include <JY901.h>

#define ANGLE_PIN (3)
#define MAX_PWM (150) 

void setup() {
  int init_angle = JY901.stcAngle.Angle[2];
  pinMode(ANGLE_PIN, OUTPUT);  
}

int a = 0;
void loop() {
 while (Serial.available()) {
    a = Serial.read();
    JY901.CopeSerialData(a); //Call JY901 data cope function
  }
  
  int pwm = (float)ANGLE(JY901.stcAngle.Angle[2] - init_angle) / 32768 * 75 + 75;
  if (pwm > MAX_PWM) { pwm -= MAX_PWM; }
  if (pwm < 0) { pwm += MAX_PWM; } 

  if (pwm < MAX_PWM) {
    analogWrite(pwm);
  }
} 
/*
float angle[3];
unsigned char Re_buf[11],counter;
unsigned char sign;
void setup() 
{
  Serial.begin(9600);
  counter = 0;
  sign = 0;
}
void usart_rx_isr() //USART 串行接收中断
{
 Re_buf[counter]=Serial.read();//不同单片机略有差异

 if(counter==0&&Re_buf[0]!=85) {
  return; //第 0 号数据不是帧头，跳过
 }
 counter++;
 if(counter==11) //接收到 11 个数据
 {
 counter=0; //重新赋值，准备下一帧数据的接收
 sign=1;
 }
}
void loop() {
  usart_rx_isr();
   if(sign)
   {
     sign=0;
     if(Re_buf[0]==85) //检查帧头
     {
        if(Re_buf [1]==83)
        {

        angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
        angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
        angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
        Serial.print( "ang");
        Serial.print( angle[0]);Serial.print(" ");
        Serial.print( angle[1]);Serial.print(" ");
        Serial.print( angle[2]);Serial.println(" ");
        }
    }
   }
 delay(500);
}*//*
unsigned char a;
unsigned char Re_buf[10];
unsigned int i ;
float angle[3];
int sign;
void setup() 
{
  Serial.begin(9600);         // Baud Rate test may values as 1200, 115200, 9600 etc..., no one works
  while (!Serial);
  Serial.print("K");            // This print is in setup loop, then sent only one time, but it appears time by time when I send bytes from the PC
  Serial.flush(); 
}
void loop() 
{
  sign = 1;
  a= Serial.readBytes();
  while (a!= 85) 
    a= Serial.read();
  a= Serial.read();
  if(a!=83) sign=0;
  for(i=0;i<9;i++){
    Re_buf[i]=Serial.read();
    if(Re_buf[i]==255||sign == 0){
      sign = 0;
      break;
    }
    Serial.println(Re_buf[i]);
  }//&& Re_buf[8] == 85+83+Re_buf[0]+Re_buf[1]+Re_buf[2]+Re_buf[3]+Re_buf[4]+Re_buf[5]+Re_buf[6]+Re_buf[7]
  if(sign == 1 ){
    angle[0] = (float(short(Re_buf [1]<<8| Re_buf [0])))/32768.0*180;
    angle[1] = (float(short(Re_buf [3]<<8| Re_buf [2])))/32768.0*180;
    angle[2] = (float(short(Re_buf [5]<<8| Re_buf [4])))/32768.0*180;
    Serial.print("Angle:");Serial.print(angle[0]);Serial.print(" ");Serial.print(angle[1]);Serial.print(" ");Serial.println(angle[2]);
  }
  delay(100);
  sign = 1;
}*/
