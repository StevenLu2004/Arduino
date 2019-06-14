#include <EEPROM.h>
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 1024; i++) {
    //EEPROM.write(i,map(analogRead(0),0,1023,0,255));
    EEPROM.write (i, analogRead (0) >> 2);
    delay(10);
  }
  digitalWrite(ledPin, HIGH);
}


void loop() {
}
