#include <EEPROM.h>
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 1024; i++) {
    EEPROM.write(i,0);
  }
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
