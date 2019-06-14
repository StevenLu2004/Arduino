#include "myUltrasoundSensor.h"

HC_SR04 distSensor = HC_SR04();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  distSensor.setPingPin(7);
  distSensor.setEchoPin(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  double dist;
  bool f = distSensor.getDistInMeters(&dist);
  if (f)
    Serial.println(dist);
  else
    Serial.println("Error");
  delay(1000);
}
