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
