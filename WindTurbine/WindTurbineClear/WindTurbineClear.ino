#include <EEPROM.h>

void setup()
{
    pinMode(13, OUTPUT);                      // Initialize LED for indication
    for (int i = 0; i < EEPROM.length(); ++i) //
        EEPROM.write(i, 0);                   // Write 0 to every byte in the EEPROM
    digitalWrite(13, HIGH);                   // Indicate process complete
}

void loop()
{
    // Do nothing
}
