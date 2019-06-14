#include <Servo.h>
#include <math.h>
#include "myUltrasoundSensor.h"

Servo lfsv = Servo();
Servo rtsv = Servo();
HC_SR04 dist = HC_SR04();

#ifndef left0
inline short _left0() {
  return 90;
}
#define left0 _left0()
#endif /* ifndef left0 */

#ifndef right0
inline double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}
inline short _right0() {
  return 90 + (sigmoid(millis() * 0.0002) - 0.5) * 5;
}
#define right0 _right0()
#endif /* ifndef right0 */

inline void setServoPair(short lval, short rval) {
  lfsv.write(left0 + lval); rtsv.write(right0 - rval);
}

void left90() {
  setServoPair(10, -10);
  delay(520);
  setServoPair(0, 0);
}

void right90() {
  setServoPair(-10, 10);
  delay(520);
  setServoPair(0, 0);
}

void forwardBlock() {
  setServoPair(30, 30);
  delay(660);
  setServoPair(0, 0);
}

void align() {
  setServoPair(10, 10);
  delay(500);
  setServoPair(0, 0);
  delay(500);
  setServoPair(-10, -10);
  delay(100);
  setServoPair(0, 0);
}

void setup() {
  // put your setup code here, to run once:
  delay(5000);
  lfsv.attach(3);
  rtsv.attach(4);
  setServoPair(0, 0);
  dist.setPingPin(7);
  dist.setEchoPin(6);
  pinMode(13, OUTPUT); digitalWrite(13, HIGH);
  delay(5000);
  /*
  for (int i = 1; i <= 10; i ++) {
    forwardBlock(); delay(1000);
    left90(); delay(1000);
    align(); delay(1000);
    right90(); delay(1000);
  }
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  setServoPair(10, 10);
}
