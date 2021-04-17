#include <Wire.h>
#include <JY901.h>

#define MAX_ANGLE (180) 
#define RIGHT_PIN (2)
#define LEFT_PIN (3)

int init_angle = 0;
int angle = 0;
int a = 0;

void setup() {
  Serial.begin(9600);
  while (Serial.available()) {
    a = Serial.read();
    JY901.CopeSerialData(a); //Call JY901 data cope function
  }
  init_angle = JY901.stcAngle.Angle[2];
  
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);    
}

void loop() {
 while (Serial.available()) {
    a = Serial.read();
    JY901.CopeSerialData(a); //Call JY901 data cope function
  }
  angle = (float)(JY901.stcAngle.Angle[2] - init_angle) / 32768 * MAX_ANGLE;
  if (angle > MAX_ANGLE) { angle -= MAX_ANGLE; }
  if (angle < -MAX_ANGLE) { angle += MAX_ANGLE; }                            


  if ((angle > 5 && angle < 30) || 
      (angle > -175 && angle < -150)) {
    // move right-backward - op[1:0] = 01   
    digitalWrite(RIGHT_PIN, HIGH);
    digitalWrite(LEFT_PIN, LOW);
  } else if ((angle > -30 && angle < -5) || 
             (angle > 150 && angle < 175)) {
    // move left-backward - op[1:0] = 10
    digitalWrite(LEFT_PIN, HIGH);
    digitalWrite(RIGHT_PIN, LOW);
  } else {
    // move backward straight - op[1:0] = 00
    digitalWrite(LEFT_PIN, LOW);
    digitalWrite(RIGHT_PIN, LOW);
  }

  return ;
} 
