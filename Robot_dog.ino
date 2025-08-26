#include <MPU6050.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <math.h>
#define SERVO_MIN 150 
#define SERVO_MAX 600 

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

typedef struct test{
    float J2;
    float J3;
}test;



void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}


double radToDeg(double rad) {
    return (rad*180) / M_PI;
}

void setServoAngle(uint8_t servoNum, float angleMin, float angle) {
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);


  pwm.setPWM(servoNum, angleMin, pulse);
}



test preForward(float Y, float Z){
test J;
float L;
float J3L = 12.5;
float B;
float J2L = 8;
float A;

L = sqrt((Y+90) * (Y+90) + (Z-60) * (Z-60));

float valJ3 = acos((J2L * J2L + J3L * J3L - L * L) / (2 * J2L * J3L));

char nan = "nan";

if (valJ3 > 1.0) valJ3 = 1.0;
if (valJ3 < -1.0) valJ3 = -1.0;
if (valJ3 = nan) valJ3 = 0.5;

J.J3 = radToDeg(valJ3);


float valB = (J2L * J2L - J3L * J3L + L * L) / (2 * J2L * L);

if (valB > 1.0) valB = 1.0;
if (valB < -1.0) valB = -1.0;

B = radToDeg(acos(valB));

A = radToDeg(atan((Z-60) / (Y+90)));


J.J2 = B - A;

J.J2 = 90 - J.J2;

return J;
}

void setForward(int servo1, int servo2, float Y, float Z){
  
  test angles = preForward(Y,Z);


if (servo1 == 4) {
    angles.J3 = 60 + angles.J3;
    angles.J2 = angles.J2 - 60;
}

  double angle1 = angles.J2;
  double angle2 = angles.J3;
}


void goStraight(){
  setServoAngle(9, 0, 70);
  setServoAngle(6, 0, 75); 
  setServoAngle(3, 0, 73);
  setServoAngle(0, 0, 170);

  setServoAngle(2,0, 60);
  setServoAngle(1,0, 70); 
  setServoAngle(8,0, 0);
  setServoAngle(7,0, 120);
  delay(3000);
  setServoAngle(2,0, 0);
  setServoAngle(1,0, 20);  
  setServoAngle(8,0, 120);
  setServoAngle(7,0, 80);

  setServoAngle(11,0, 0);
  setServoAngle(10,0, 90); 
  setServoAngle(5,0, 90);
  setServoAngle(4,0, 150);
  delay(3000);
  setServoAngle(11,0, 80);
  setServoAngle(10,0, 140);  
  setServoAngle(5,0, 20);
  setServoAngle(4,0, 100);
};

void pause(){
  setServoAngle(2,0, 90);
  setServoAngle(1,0, 70); 
  setServoAngle(8,0, 90);
  setServoAngle(7,0, 120);
  setServoAngle(11,0, 20);
  setServoAngle(10,0, 90); 
  setServoAngle(5,0, 90);
  setServoAngle(4,0, 150);  
  
  setServoAngle(9, 0, 55);
  setServoAngle(6, 0, 75); 
  setServoAngle(3, 0, 73);
  setServoAngle(0, 0, 170);
}



void loop() {
setForward(10, 11, -72,80);
setForward(7, 8, 0,42);
setForward(4, 5, -75, 100);
setForward(2, 1, 10, 0);
delay(4000); 
pause();
delay(4000);

}
