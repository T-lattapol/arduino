//-*- mode: c -*-
/* 
 * NAME
 *     Blinker
 * PURPOSE
 *     A little module to blink the LED on an Arduino for debugging and reassurance and state feedback.
 * AUTHOR
 *     Scott BARNES 2017/2018. IP freely on non-commercial applications.
 * PROTOCOL FROM HOST
 *     None (though this would be a good thing to do later to control the blink pattern from the host).
 * PROTOCOL TO HOST
 *     None.
 * PHILOSOPHY
 * A human can reliable distiguish blinking lights at about 75ms (ie between state changes, hence a blink every 150ms).
 * We use a number of patterns which a human could describe to another human over the phone (eg one blink and then two).
 * Consequently a number of patterns are not distinguishable (eg 'one blink, then another blink' is not distinguishable from 'two blinks').
 * So the patterns are
 * * one blink then two blinks       (0x00000501)
 * * one blink then three blinks     (0x00001501)
 * * two blinks then one blink       (0x00000105)
 * * two blinks then two blinks      (0x00000505)
 * * two blinks then three blinks    (0x00001505)
 * * three blinks then one blink     (0x00000115)
 * * three blinks then two blinks    (0x00000515)
 * * three blinks then three blinks  (0x00001515)
 * We use the one-blink starters for 'start-up' - (eg 'init', 'contacting lidar', 'starting motor')
 * We use the two-blink starters for 'running-states' (eg 'moving', 'pausing to think')
 * We use the three-blink starters for 'error-states' (eg 'engine stalled', 'I've driven into the dam', ..)
 */

#ifndef Blinker_h
#define Blinker_h

#include <Arduino.h>
#include "King.h"

#define BLINK_PATTERN_12 0x00000501  /* one blink then two blinks      - 'the system has started, and is in the first stage of the startup sequence' */
#define BLINK_PATTERN_13 0x00001501  /* one blink then three blinks    - 'the system is running, and is in the second stage of the startup sequence' */
#define BLINK_PATTERN_21 0x00000105  /* two blinks then one blink      - 'the system is running, and is in the operational state _one_' */
#define BLINK_PATTERN_22 0x00000505  /* two blinks then two blinks     - 'the system is running, and is in the operational state _two_' */
#define BLINK_PATTERN_23 0x00001505  /* two blinks then three blinks   - 'the system is running, and is in the operational state _three_' */
#define BLINK_PATTERN_31 0x00000115  /* three blinks then one blink    - 'the system is in error state _one_' */
#define BLINK_PATTERN_32 0x00000515  /* three blinks then two blinks   - 'the system is in error state _two_' */
#define BLINK_PATTERN_33 0x00001515  /* three blinks then three blinks - 'the system is in error state _three_' */

class Blinker : public King {
private:
    byte pin;             // Which pin the LED is on. 13 on the Nano.
    uint32_t pattern;     // 32-bit pattern eg 0x00000505 is two-then-two.
    byte blinkPosition;    // Where in the 32-bit mask we currently are.
    uint32_t nextBlinkAt; // When millis() is at this value, we display the next bit.
public:
    Blinker(byte pin = LED_BUILTIN);
    void setBlinkPattern(uint32_t blinkPattern);
    virtual void setup();
    virtual void loop(uint32_t now);
    virtual void command(char *commandLine) {};
};

#endif /* Blinker_h */
