#include <EEPROM.h>
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 1024; i++){
    Serial.print(i);
    Serial.print(", ");
    Serial.println(EEPROM.read(i));
  }
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
