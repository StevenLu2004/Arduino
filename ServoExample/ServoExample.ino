#include <Servo.h>
#include "myUltrasoundSensor.h"

Servo lfServo = Servo();
Servo rtServo = Servo();
HC_SR04 distSensor = HC_SR04();

long d0 = 0;
bool fturnright = false;

/**
 * setServoPair sets a servo pair, with 90 being full forward and -90 being full backward
 */
inline void setServoPair(short lval = 0, short rval = 0) {
  lfServo.write(90 + lval); rtServo.write(92 - rval);
}

const short STOP = 0, FORWARD = 2, LEFT = -1, RIGHT = 1;
short SERVOSTAT = STOP;
inline void updateServo(short stat) {
  if (stat == SERVOSTAT) return;
  switch (stat) {
    case STOP:
      setServoPair();
      break;
    case FORWARD:
      setServoPair(10, 8);
      break;
    case LEFT:
      setServoPair(-10, 10);
      break;
    case RIGHT:
      setServoPair(10, 4);
      break;
  }
  SERVOSTAT = stat;
}

void setup() {
  // put your setup code here, to run once:
  delay(5000);
  lfServo.attach(3);
  rtServo.attach(4);
  updateServo(STOP);
  distSensor.setPingPin(7);
  distSensor.setEchoPin(6);
  bool f = distSensor.getDistInMicroseconds(&d0);
  pinMode(13, OUTPUT); digitalWrite(13, f ? HIGH : LOW);
  if (!f) d0 = -1;
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  long d;
  bool f = distSensor.getDistInMicroseconds(&d);
  digitalWrite(13, (f && d0 > 0) ? HIGH : LOW);
  if (!f || d0 <= 0) {
    updateServo(STOP);
    return;
  }
  if (d < d0 - 60) {
    updateServo(LEFT);
    fturnright = false;
  } else if (d > d0 + 60) {
    if (!fturnright) {
      updateServo(FORWARD);
      delay(100);
      fturnright = true;
      updateServo(RIGHT);
    } else {
      updateServo(RIGHT);
    }
  } else {
    updateServo(FORWARD);
    fturnright = false;
  }
}
