#include <time.h>
#include <math.h>

/* ************************ *\
|*         SETTINGS         *|
\* ************************ */

const short DELAY_LENGTH = 1000;                                         // Delay between two readouts
const long READ_REPEAT = 1000;                                           // Repeatedly read this many times and take the average [read]
const double VOL_LIM = 5.0;                                              // Voltage limit on readout, can be 5.0 or 1.1 [calcV]
const double R_0 = 1e4, V_0 = 5.0;                                       // Constant resistance and total voltage [calcR]
const double A = 1.72256531e-03, B = 2.15127196e-04, C = 3.93630218e-07; // A, B and C required for temperature calculation, calibration needed [calcT]
const double DIG_KEEP = 10;                                              // Determines how many digits of temperature are kept
const unsigned char LED_PINS[] = {10, 11, 12};                           // The LED pins to use for showing temperature range, in the order of R, G, B

// In case they give us discontinuous ranges, etc.
bool goRed(double);   // Judgement function for whether the red LED should be on
bool goGreen(double); // Judgement function for whether the green LED should be on
bool goBlue(double);  // Judgement function for whether the blue LED should be on

bool goRed(double temp)
{
    // Stub
    return false;
}
bool goGreen(double temp)
{
    // Stub
    return false;
}
bool goBlue(double temp)
{
    // Stub
    return false;
}

/* ************************ *\
|*           CORE           *|
\* ************************ */

double toCelsius(double);

double read();
double calcV(double);
double calcR(double);
double calcT(double);
double print(unsigned long, double, double, double); // Print everything: timestamp, raw, vol, res, temp
double respond(double);                              // Respond to temperature via LEDs

void setup();
void loop();

double toCelsius(double K)
{
    return K - 273.15;
}

double read()
{
    long rawSum = 0;
    for (int i = 0; i < READ_REPEAT; ++i)
        rawSum += analogRead(A0);
    return (double)rawSum / READ_REPEAT; // Type caste
}

double calcV(double raw)
{
    return raw * VOL_LIM / 1023;
}

/**
 * Calculate resistance of thermistor
 * R = V * R_0 / (V_0 - V)
 * @param V voltage readout
 * @return resistance of thermistor
 */
double calcR(double V)
{
    return V * R_0 / (V_0 - V);
}

/**
 * Calculate temperature on thermistor
 * 1/T = A + B * ln(R) + C * ln(R)**3
 * @param R resistance from calcR
 * @return temperature in degrees Celsius
 */
double calcT(double R)
{
    double logR = log(R);
    return toCelsius(1 / (A + (B * logR) + (C * logR * logR * logR)));
}

void print(unsigned long timeStamp, double raw, double vol, double res, double temp)
{
    Serial.print("Voltage: ");
    Serial.print(vol);
    Serial.print("; ");
    Serial.print("Temperature: ");
    Serial.print((int)(temp * DIG_KEEP + 0.5) / DIG_KEEP); // Round
    Serial.print(" [");
    Serial.print("timeStamp=");
    Serial.print(timeStamp);
    Serial.print("raw=");
    Serial.print(raw);
    Serial.print("res=");
    Serial.print(res);
    Serial.println("]");
}

double respond(double temp)
{
    digitalWrite(LED_PINS[0], goRed(temp));
    digitalWrite(LED_PINS[1], goGreen(temp));
    digitalWrite(LED_PINS[2], goBlue(temp));
}

void setup()
{
    for (int i = 0; i < 3; ++i)
        pinMode(LED_PINS[i], OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    delay(DELAY_LENGTH);
    double raw = read();
    double vol = calcV(raw);
    double res = calcR(vol);
    double temp = calcT(res);
    double timeStamp = millis();
    print(timeStamp, raw, vol, res, temp);
    respond(temp);
}

//  1.0 -> 3000
// 35.6 -> 689
// 65.5 -> 227

// 274.2 -> 3000
// 308.8 -> 689
// 338.7 -> 227
