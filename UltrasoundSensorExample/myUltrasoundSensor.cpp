#ifndef myUltrasoundSensor_cpp
#define myUltrasoundSensor_cpp

#include <Arduino.h>
#include "myUltrasoundSensor.h"

HC_SR04::HC_SR04() {
  this->pingPin = -1;
  this->echoPin = -1;
  this->speedOfSound = 340.0;
  this->distanceBias = 0.0;
}

short HC_SR04::getPingPin() const {
  return this->pingPin;
}

bool HC_SR04::setPingPin(const short pingPin) {
  if (pingPin >= 0 && pingPin <= 13 && pingPin != this->echoPin) {
    this->pingPin = pingPin;
    pinMode(this->pingPin, OUTPUT);
    return true;
  } else {
    return false;
  }
}

short HC_SR04::getEchoPin() const {
  return this->echoPin;
}

bool HC_SR04::setEchoPin(const short echoPin) {
  if (echoPin >= 0 && echoPin <= 13 && echoPin != this->pingPin) {
    this->echoPin = echoPin;
    pinMode(this->echoPin, INPUT);
    return true;
  } else {
    return false;
  }
}

bool HC_SR04::swapPins() {
  if ((this->pingPin >= 0 && this->pingPin <= 13) && (this->echoPin >= 0 && this->echoPin <= 13) && this->pingPin != this->echoPin) {
    short t = this->pingPin; this->pingPin = this->echoPin; this->echoPin = t;
    pinMode(this->pingPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
    return true;
  } else {
    return false;
  }
}

double HC_SR04::getSpeedOfSound() const {
  return this->speedOfSound;
}

bool HC_SR04::setSpeedOfSound(const double speedOfSound) {
  if (speedOfSound > 0.0) {
    this->speedOfSound = speedOfSound;
    return true;
  } else {
    return false;
  }
}

double HC_SR04::getDistanceBias() const {
  return this->distanceBias;
}

bool HC_SR04::setDistanceBias(const double distanceBias) {
  this->distanceBias = distanceBias;
  return true;
}

bool HC_SR04::getDistInMicroseconds(long *distInMicroseconds) const {
  if ((this->pingPin >= 0 && this->pingPin <= 13) && (this->echoPin >= 0 && this->echoPin <= 13) && this->pingPin != this->echoPin && distInMicroseconds) {
    pinMode(this->pingPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
    // Send ping
    digitalWrite(this->pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->pingPin, LOW);
    // Recv echo
    long res = pulseIn(this->echoPin, HIGH, 100000);
    if (res == 0) return false;
    *distInMicroseconds = res;
    return true;
  } else {
    return false;
  }
}

bool HC_SR04::getDistInMeters(double *distInMeters) const {
  if ((this->pingPin >= 0 && this->pingPin <= 13) && (this->echoPin >= 0 && this->echoPin <= 13) && this->pingPin != this->echoPin && distInMeters) {
    long duration;
    bool f = getDistInMicroseconds(&duration);
    if (!f) return false;
    *distInMeters = (double(duration) * 1e-6 * this->speedOfSound + distanceBias) / 2.0;
    return true;
  } else {
    return false;
  }
}

#endif /* ifndef myUltrasoundSensor_cpp */
