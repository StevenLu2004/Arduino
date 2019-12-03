#include <EEPROM.h>
#include <time.h>

const uint8_t LED = 13; // Arduino LED pin is 13

long voltage;        // Sum of voltage samples in current interval
long samplesz;       // Sample size of current interval
short avgVoltage;    // Average voltage of current interval
unsigned long count; // Count the occurrences of a particular voltage
unsigned long t;     // Time

/**
 * Clears the EEPROM. Not being used RN.
 */
void clear()
{
    for (int i = 0; i < EEPROM.length(); i++)
        EEPROM.write(i, 0);
}

void setup()
{
    // clear(); // Commented to avoid data loss
    analogReference(INTERNAL); // Use INTERNAL (1.1V) reference
    Serial.begin(9600);        // Initialize Serial for debug
    t = millis();              // Take current time // clock() and clock_t are not implemented, because Arduino thinks that they are OS/App level API. The alternatives are millis() and micros(), available in the time.h source file in the Arduino app distribution.
    pinMode(LED, OUTPUT);      // Initialize LED pin mode
}

void loop()
{
    // Repeatedly take voltage, get sum and sample size
    samplesz = 0;
    voltage = 0; // zero
    while (t + 1000 > millis())
    {
        // Take average of voltage
        voltage += analogRead(A0);
        ++samplesz;
    }

    // Debug check for overflow
    digitalWrite(LED, samplesz >= 65536);

    // Update time variable
    t += 1000;

    // Round down average voltage
    avgVoltage = double(voltage) / double(samplesz);
    Serial.println(avgVoltage); // Debug

    // Increment voltage counter
    EEPROM.get(avgVoltage << 2, count);     // Get count from that address
    EEPROM.put(avgVoltage << 2, count + 1); // Increment that address by 1
}
