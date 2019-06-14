#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  for (int i = 0; i < 1024; i ++) {
    int val = EEPROM.read (i);
    EEPROM.write (i, 0);
    Serial.print (i);
    Serial.print ("\t");
    Serial.print (val);
    Serial.println ();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
