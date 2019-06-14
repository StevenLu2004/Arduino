// myUltrasoundSensor: a better library for 4-pin Arduino ultrasonic sensors
// Copyright (C) 2019  Tongyu Lu (Steven)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef myUltrasoundSensor_cpp
#define myUltrasoundSensor_cpp

#include <Arduino.h>
#include "myUltrasoundSensor.h" // Implements the library

/**
 * Class constructor
 */
HC_SR04::HC_SR04() {
  this->pingPin = -1;
  this->echoPin = -1;
  this->speedOfSound = 340.0;
  this->distanceBias = 0.0;
}

/**
 * Returns the ping pin
 */
short HC_SR04::getPingPin() const {
  return this->pingPin;
}

/**
 * Sets the ping pin
 */
bool HC_SR04::setPingPin(const short pingPin) {
  if (pingPin >= 0 && pingPin <= 13 && pingPin != this->echoPin) {
    this->pingPin = pingPin;
    pinMode(this->pingPin, OUTPUT);
    return true;
  } else {
    return false;
  }
}

/**
 * Returns the echo pin
 */
short HC_SR04::getEchoPin() const {
  return this->echoPin;
}

/**
 * Sets the echo pin
 */
bool HC_SR04::setEchoPin(const short echoPin) {
  if (echoPin >= 0 && echoPin <= 13 && echoPin != this->pingPin) {
    this->echoPin = echoPin;
    pinMode(this->echoPin, INPUT);
    return true;
  } else {
    return false;
  }
}

/**
 * Swaps the pins if both are valid. If no spare pins are present, this function allows for swapping the ping and echo pins.
 */
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

/**
 * Returns the speed of sound in double
 */
double HC_SR04::getSpeedOfSound() const {
  return this->speedOfSound;
}

/**
 * Sets the speed of sound in double
 */
bool HC_SR04::setSpeedOfSound(const double speedOfSound) {
  if (speedOfSound > 0.0) {
    this->speedOfSound = speedOfSound;
    return true;
  } else {
    return false;
  }
}

/**
 * Returns the distance biase constant in double
 */
double HC_SR04::getDistanceBias() const {
  return this->distanceBias;
}

/**
 * Sets the distance biase constant in double
 */
bool HC_SR04::setDistanceBias(const double distanceBias) {
  this->distanceBias = distanceBias;
  return true;
}

/**
 * Returns the distance in µs
 */
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

/**
 * Returns the distance in meters by calling the getDistInMicroseconds function first
 */
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
