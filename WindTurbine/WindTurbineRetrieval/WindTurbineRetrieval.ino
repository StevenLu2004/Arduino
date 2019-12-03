#include <EEPROM.h>

const uint8_t LED = 13; // Arduino LED is 13

long a; // Placeholder throwaway variable

/**
 * Flash the LED many times at certain interval
 * @param x the number of times to flash
 * @param d the interval in milliseconds
 */
void flash(int x = 5, int d = 200)
{
    for (int i = 0; i < x; ++i)
    {
        digitalWrite(LED, HIGH);
        delay(d / 2);
        digitalWrite(LED, LOW);
        delay(d / 2);
    }
}

void setup()
{
    Serial.begin(9600);              // Set up Serial for transmission
    Serial.setTimeout(600L * 1000L); // Set timeout to 10 minutes
    pinMode(LED, OUTPUT);            // Initialize LED
}

void loop()
{
    while (Serial.readStringUntil('\n') != "connect") // Wait for trigger string
        flash();                                      // Flash 5 times when trigger string doesn't match
    Serial.println("connected");                      // Serial feedback to successful connection
    Serial.flush();                                   // Flush Serial buffer // Is this really needed?
    flash(10);                                        // Flash 10 times when trigger string matches
    for (int i = 0; i < 256; ++i)                     // Loop through long addresses (voltages) in EEPROM
    {                                                 //
        EEPROM.get(i << 2, a);                        // Get the count of the voltage
        Serial.println(a);                            // Send through Serial
    }                                                 //
    Serial.flush();                                   // Flush Serial buffer // Is this really needed?
}
