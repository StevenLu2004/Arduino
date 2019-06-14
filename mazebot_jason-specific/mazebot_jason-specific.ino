#include <Servo.h>
#include "myUltrasoundSensor.h" // Uses the library

Servo lfsv = Servo(); // Left servo
Servo rtsv = Servo(); // Right servo
HC_SR04 dist = HC_SR04(); // Ultrasonic sensor

const short left0 = 91, right0 = 90; // Values at which the two servos converge to a stop
const long l90delay = 490, r90delay = 520, blockDelay = 870, restDelay = 1000; // Delay time in milliseconds for turning left 90 deg, right 90 deg, going forward a block and rest
const long edgeDis = 600; // Edge distance represented in microseconds for judging whether the front is blocked by a wall. If detected dist in µs is smaller than this number, the robot treats the situation as being blocked by a wall.
long dis; // Storage space for detected distance
bool fdis; // Storage space for whether the getDistInMicroseconds function succeed. If false, the robot rests and tests distance again.

/**
 * Sets both servos according to input values and 0 values
 * @param lv: value for left servo, positive for forward
 * @param rv: value for right servo, positive for forward
 */
void moveAt(short lv, short rv) {
  lfsv.write(left0 + lv); rtsv.write(right0 - rv);
}

/**
 * Let the robot turn left 90 deg
 */
void left90() {
  moveAt(-10, 10);
  delay(l90delay);
  moveAt(0, 0);
  delay(restDelay);
}

/**
 * Let the robot turn right 90 deg
 */
void right90() {
  moveAt(10, -10);
  delay(r90delay);
  moveAt(0, 0);
  delay(restDelay);
}

/**
 * Aligns the robot by commanding it to push against the wall in the front and stepping back a bit. This function is key to keeping the direction of the robot.
 */
void align() {
  moveAt(10, 10);
  delay(3000);
  moveAt(0, 0);
  delay(500);
  moveAt(-10, -10);
  delay(300);
  moveAt(0, 0);
  delay(restDelay);
}

/**
 * Makes the robot go forward one tile
 */
void forwardBlock() {
  moveAt(11, 10);
  delay(blockDelay);
  moveAt(0, 0);
  delay(restDelay);
}

/**
 * Setup code.
 * Waits 5 sec, then sets up everything and turns on LED as indication, then waits another 5 sec
 */
void setup() {
  delay(5000);
  lfsv.attach(3);
  rtsv.attach(4);
  moveAt(0, 0);
  dist.setPingPin(7);
  dist.setEchoPin(6);
  pinMode(13, OUTPUT); digitalWrite(13, HIGH);
  delay(5000);
}

/**
 * Loop code.
 * On a new tile, turn right 90 deg;
 * Repeat testing distance in the front;
 * If testing failed, wait;
 * If blocked, align and turn lieft 90 deg;
 * If free to go, break the loop and go forward a tile.
 */
void loop() {
  right90();
  while (true) {
    fdis = dist.getDistInMicroseconds(&dis);
    if (!fdis) {
      delay(1000);
      continue;
    }
    if (dis > edgeDis) break;
    align();
    left90();
  }
  forwardBlock();
}
