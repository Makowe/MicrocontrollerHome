#include "debug.h"
#include "ledInterface.h"
#include "theme/themeRainbow.h"
#include <Arduino.h>
#include <filter/filterPulsate.h>
#include "options/remote.h"

#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false
#define USE_TIMER_4     false
#define USE_TIMER_5     false
#define TIMER1_INTERVAL_MS 100

#include "../lib/Arduino-IRremote-3.9.0/src/IRremote.h"
#include "../lib/TimerInterrupt-1.8.0/src/TimerInterrupt.h"

#define DECODE_NEC
#include "options/remote.h"


//
// GLOBALS
//

LedInterface led;

ThemeRainbow rainbowTheme = ThemeRainbow(RAINBOW_DEFAULT_SPEED, RAINBOW_DEFAULT_COMPRESS);
Theme* theme = &rainbowTheme;

FilterPulsate filterPulsate = FilterPulsate(PULSATE_DEFAULT_SPEED);
Filter* filter = &filterPulsate;

IRrecv irrecv(IR_IN_PIN);
decode_results results;
unsigned lockIR = 0;
bool lockLeds = true;

void TimerHandler1() {
#if DEBUG_MAIN
    Serial.println("[MAIN]: Timer 1 Interrupt");
#endif
    lockLeds = false;
}

void updateLeds() {
#if DEBUG_LEDS
    Serial.println("[LEDS]: Update LEDs");
#endif

    theme->nextTick();
    filter->nextTick();

    for (unsigned int pixel_idx = 0; pixel_idx < NUM_PIXELS; pixel_idx++) {
        Color color = theme->calcTheme(pixel_idx);
        color = filter->applyFilter(pixel_idx, color);
        led.setColor(pixel_idx, color);
    }
}

void setup() {

    Serial.begin(9600);

#if DEBUG_MAIN
    Serial.println("[MAIN]: Setup");
#endif

    pinMode(IR_IN_PIN, INPUT);

    pinMode(IR_LOW_PIN, OUTPUT);
    pinMode(IR_HIGH_PIN, OUTPUT);
    digitalWrite(IR_LOW_PIN, LOW);
    digitalWrite(IR_HIGH_PIN, HIGH);

    irrecv.enableIRIn();

    ITimer1.init();
    ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1);
}

void loop() {

#if DEBUG_MAIN
    Serial.print("[MAIN]: Loop");
#endif

    bool newSignal = irrecv.decode();
    if (newSignal)
    {
        if(irrecv.decodedIRData.flags == 0 || lockIR == 0) {

#if DEBUG_REMOTE
            print_detected_button(irrecv.decodedIRData.command);
#endif
            lockIR = IR_LOCK_TIME;
            buttonClicked(irrecv.decodedIRData.command);
        }
        else {
#if DEBUG_REMOTE
            print_detected_button(irrecv.decodedIRData.command, true);
#endif
            lockIR -= 1;
        }
        irrecv.resume();
    }

    if(!lockLeds) {
        lockLeds = true;
        updateLeds();
        led.show();
    }
}
