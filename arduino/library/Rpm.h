//-*- mode: c -*-
/* 
 * UNTESTED/WIP
 *     ************ UNTESTED AS AT 2018-10-03.
 * NAME
 *     Rpm.h
 * PRECIS
 *     An arduino-based RPM meter - which recieves pulses on the interrupt pin (probably from a spark plug clamp), and periodically sends the interrupts-per-minute as bytes on the Serial port.
 * COPYRIGHT
 *     Scott BARNES 2016. IP freely on non-commercial applications.
 * DETAILS
 *     Some RPM meters have a inductive clamp which goes around the spark-plug lead.
 *     This will produce a short pulse whenever the spark plug fires.
 *     This pulse may be very high voltage, and is likely to fry the arduino chip, so it must be regulated - (A clamping diode and voltage divider may work, or something more sophisticated may be required).
 *     This (regulated) pulse causes an interrupt routine to be called on the arduino, which records the time between pulses.
 *     Periodically, a byte is sent on the Serial output representing the current (or smoothed/recent) RPM.
 * WARNING
 *      The Arduino MUST be protected from high voltage.
 *      Some 4-stroke engines use a 'wasted spark', some don't. So it may be necessary to double the reported RPM to get the actual value, or it may not. Suck it and see.
 * OUTPUT TO HOST
 *      Host will receive a packet every REFRESH_INTERVAL_MS milliseconds (eg 100 == 10 times per second, check the code).
 *      Multiply this (unsigned) byte by 32 to get the RPM.
 *      "Rxx" (xx is rpm >> 5)
 * ALGORITHM
 *      Smoothing is done by a modified exponential smoothing filter. The smoothiness depends on the ALPHA value.
 *      The output byte is (rpm >> 5) which will give a range of (0..8160) RPM and a resolution of 32 RPM.
 *      Good enough for the bush, and must simpler than using a complex packet-based sending approach.
 * PHILOSOPHY
 *      The sparks cause a voltage drop, which calls an interrupt, the interrupt maintains the 'smoothedRpm' value.
 *      The normal Arduino 'loop()' call sends the current value to the host every REFRESH_INTERVAL_MS.
 *      This means the host will be receiving updates at a constant rate regardless of the RPM of the motor.
 * PLAYING WITH OTHERS
 *      In principle this could co-exist with other modules such as the ParkingSensor1 or ParkingSensor2 modules, however the protocol
 *      would have to to be modified to distinguish between packet types.
 * TESTING
 * AS AT 2018-10-01 THIS IS UNTESTED.
 * 
 * BUGS
 * Ignores the SENSOR pin passed to constructor. Always uses pin D3.
 */

#ifndef Rpm_h
#define Rpm_h

#include <Arduino.h>

#define DEFAULT_SPARKPLUG_READ_PIN    3 // Only pins 2 and 3 are capable of this function on the Nano

class Rpm {
public:
    Rpm(byte pin = DEFAULT_SPARKPLUG_READ_PIN);
    void setup();
    void loop(uint32_t now);
private:
    byte pin;
    void initializePins(void);
    void sendRpmViaSerialPort();
    static char *hex;
    static unsigned long previousMillis;
    static volatile int smoothedRpm;
    static void pulseReceived();
};

#endif /* Rpm_h */