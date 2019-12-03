#include <time.h>
#include <math.h>

/* ************************ *\
|*         SETTINGS         *|
\* ************************ */

const short DELAY_LENGTH = 1000;   // Delay between two readouts
const short READ_REPEAT = 1000000; // Repeatedly read this many times and take the average [read]
const double VOL_LIM = 5.0;        // Voltage limit on readout, can be 5.0 or 1.1 [calcV]
double R_0 = 1e4;                  // [Settable] Constant R [calcR]
const double V_0 = 5.0;            // Total voltage [calcR]
double A = 0, B = 0, C = 0;        // [Settable] A, B and C required for temperature calculation, calibration needed [calcT]
const double DIG_KEEP = 10;        // Determines how many digits of temperature are kept
// Remove LED support; set manually in DetectorRead.ino

/* ************************ *\
|*           CORE           *|
\* ************************ */

double read();
double calcV(double);
double calcR(double);
double calcT(double);
double print(unsigned long, double, double, double); // Print everything: timestamp, raw, vol, res, temp
// Remove LED support; set manually in DetectorRead.ino

void setup();
void loop();

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
    return 1 / (A + (B * logR) + (C * logR * logR * logR));
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

void setup()
{
    // for (int i = 0; i < 3; ++i)
    //     pinMode(LED_PINS[i], OUTPUT);
    // Serial.begin(9600);
}

void loop()
{
    // delay(DELAY_LENGTH);
    // double raw = read();
    // double vol = calcV(raw);
    // double res = calcR(vol);
    // double temp = calcT(res);
    // double timeStamp = millis();
    // print(timeStamp, raw, vol, res, temp);
    // respond(temp);
}

/* ************************ *\
|*        CALIBRATE_        *|
\* ************************ */

// Goals
// - Semi-autodetect constant R
// - Solve for A, B and C using Gaussian elimination (move out?)
