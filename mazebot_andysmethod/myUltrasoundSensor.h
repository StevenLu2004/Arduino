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

#ifndef myUltrasoundSensor_h
#define myUltrasoundSensor_h

#include <Arduino.h>

class HC_SR04 {
public:
  HC_SR04();

  short getPingPin() const;
  bool setPingPin(const short pingPin);
  short getEchoPin() const;
  bool setEchoPin(const short echoPin);
  bool swapPins();
  double getSpeedOfSound() const;
  bool setSpeedOfSound(const double speedOfSound);
  double getDistanceBias() const;
  bool setDistanceBias(const double distanceBias);

  bool getDistInMicroseconds(long *distInMicroseconds) const;
  bool getDistInMeters(double *distInMeters) const;

private:
  short pingPin, echoPin;
  double speedOfSound, distanceBias;
};

#endif /* ifndef myUltrasoundSensor_h */
