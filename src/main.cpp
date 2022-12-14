#include "constants.h"
#include "debug.h"
#include "ledInterface.h"
#include "options/remote.h"
#include "theme/instances/themeRainbow.h"
#include <Arduino.h>
#include <filter/filterHandler.h>
#include <filter/instances/filterPulsate.h>
#include <theme/themeHandler.h>

#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false
#define USE_TIMER_4     false
#define USE_TIMER_5     false
#define TIMER1_INTERVAL_MS 100

#include "../lib/Arduino-IRremote-3.9.0/src/IRremote.h"
#include "../lib/TimerInterrupt-1.8.0/src/TimerInterrupt.h"

#define DECODE_NEC

//
// GLOBALS
//

LedInterface led;
unsigned int timeSinceLastButtonProcess = 0;

IRrecv irrecv(IR_INPUT_PIN);
decode_results results;
unsigned int IRButtonHold = 0;

bool discardNextIrSignal = true;

void TimerHandler1() {
    timeSinceLastButtonProcess++;
}

void updateLeds() {
#if DEBUG_LEDS
    Serial.println("[LEDS]: Update LEDs");
#endif

    currentTheme->nextTick();
    currentFilter->nextTick();

    for (unsigned int pixel_idx = 0; pixel_idx < NUM_PIXELS; pixel_idx++) {
        Color color = currentTheme->calcTheme(pixel_idx);
        color = currentFilter->applyFilter(pixel_idx, color);
        led.setColor(pixel_idx, color);
    }
}

void setup() {

    Serial.begin(9600);

#if DEBUG_MAIN
    Serial.println("[MAIN]: Setup");
#endif

    pinMode(IR_INPUT_PIN, INPUT);

    pinMode(IR_LOW_PIN, OUTPUT);
    pinMode(IR_HIGH_PIN, OUTPUT);
    digitalWrite(IR_LOW_PIN, LOW);
    digitalWrite(IR_HIGH_PIN, HIGH);

    irrecv.enableIRIn();

    ITimer1.init();
    ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1);

    initThemes();
    initFilters();
}

void loop() {

    bool newSignal = irrecv.decode();
    if (newSignal)
    {
        if(timeSinceLastButtonProcess < IR_BLOCK_DELAY_AFTER_EDIT) {
            /* The IR is blocked because the user just switched from editing to running mode. */
        }
        else if(discardNextIrSignal) {
            /* The button signal is ignore because it was just used to switch into editor mode. */
            discardNextIrSignal = false;
        }
        else if(timeSinceLastButtonProcess < IR_BUTTON_HOLD_DELAY) {
            /* The button has already been processed. It needs to be held for a longer time to be processed again. */
#if DEBUG_REMOTE
            print_detected_button(irrecv.decodedIRData.command, true);
#endif
        }
        else if(irrecv.decodedIRData.flags == 0 || timeSinceLastButtonProcess == IR_BUTTON_HOLD_DELAY) {
            /* The signal is either new or the button is held for a certain time and therefore processed again. */
#if DEBUG_REMOTE
            print_detected_button(irrecv.decodedIRData.command);
#endif
            if(discardNextIrSignal) {
                discardNextIrSignal = false;
            }
            else {
                buttonClicked(irrecv.decodedIRData.command);
                updateLeds();
                led.show();
                timeSinceLastButtonProcess = 0;
            }
        }
        irrecv.resume();
    }

    if(LedMode == LED_MODE_RUNNING && timeSinceLastButtonProcess >= IR_BLOCK_DELAY_AFTER_EDIT && !digitalRead(IR_INPUT_PIN)) {
#if DEBUG_REMOTE
        Serial.println("[REMOTE]: Switch to Editor Mode");
#endif
        LedMode = LED_MODE_EDIT;
    }

    if(LedMode == LED_MODE_RUNNING) {
        discardNextIrSignal = true;
        updateLeds();
        led.show();
    }
}
