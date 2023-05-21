
#include <Arduino.h>
#include <IRremote.h>

/* define before including the TimerInterrupt */
#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false
#define USE_TIMER_4     false
#define USE_TIMER_5     false
#define TIMER1_INTERVAL_MS 1000

#include <TimerInterrupt.h>

#include "constants.h"
#include "debug.h"
#include "ledInterface.h"
#include "options/remote.h"
#include "filter/filterHandler.h"
#include "theme/themeHandler.h"



#define DECODE_NEC

//
// GLOBALS
//

LedInterface led;
unsigned int timeSinceLastButtonProcess = 0;
bool blockLeds = false;

IRrecv irrecv(IR_INPUT_PIN);
decode_results results;

bool discardNextIrSignal = true;

//
// Interrupt Service Routines
//

void TimerHandler1() {
    PRINT_DEBUG_MSG(DEBUG_LEDS, "[MAIN]: Timer Interrupt");
    timeSinceLastButtonProcess++;
    blockLeds = false;
}

//
// Functions
//

void updateLeds() {
    PRINT_DEBUG_MSG(DEBUG_LEDS, "[LEDS]: Update LEDs");

    currentTheme->nextTick();
    currentFilter->nextTick();

    for (unsigned int pixel_idx = 0; pixel_idx < NUM_PIXELS; pixel_idx++) {
        Color color = currentTheme->calcTheme(pixel_idx);
        color = currentFilter->applyFilter(pixel_idx, color);
        led.setColor(pixel_idx, color);
    }
}

//
// Arduino Entry Points
//

void setup() {

    Serial.begin(9600);

    PRINT_DEBUG_MSG(DEBUG_MAIN, "[Main]: Setup");

    pinMode(IR_INPUT_PIN, INPUT);

    pinMode(IR_LOW_PIN, OUTPUT);
    pinMode(IR_HIGH_PIN, OUTPUT);
    digitalWrite(IR_LOW_PIN, LOW);
    digitalWrite(IR_HIGH_PIN, HIGH);

    pinMode(0, INPUT);

    irrecv.enableIRIn();

    ITimer1.init();
    ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1);

    initThemes();
    initFilters();
}

void loop() {

    bool newSignal = irrecv.decode();
    if (LedMode == LED_MODE_EDIT && newSignal) {
        /* A new signal has been decoded. It can either by caused by pressing a new button or holding an already processed button. */

        if(discardNextIrSignal) {
            /* The button signal is ignore because it was just used to switch into editor mode. */

            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[Remote]: Button signal is ignored because it was only used to switch to editor mode");
            discardNextIrSignal = false;
        }
        else if(irrecv.decodedIRData.flags && timeSinceLastButtonProcess < IR_BUTTON_HOLD_DELAY) {
            /* The button has already been processed but it is not held long enough to be processed again. */
            RUN_DEBUG_FUNCTION(DEBUG_REMOTE, print_detected_button(irrecv.decodedIRData.command, true));
        }
        else {
            /* The signal is either new or the button is held long enough to be processed again. */
            RUN_DEBUG_FUNCTION(DEBUG_REMOTE, print_detected_button(irrecv.decodedIRData.command));
            bool validButton = processButtonClick(irrecv.decodedIRData.command);

            /* update LEDs once to show user what the new setting looks like */
            if(validButton) {
                updateLeds();
                led.show();
                timeSinceLastButtonProcess = 0;
            }
        }
        irrecv.resume();
    }

    if(LedMode == LED_MODE_RUNNING && timeSinceLastButtonProcess >= IR_BLOCK_DELAY_AFTER_EDIT && !digitalRead(IR_INPUT_PIN)) {
        /* In running mode while the LED is not blocked, an IR signal has been detected. */
        PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch to Editor Mode", NEW_LINE_AFTER);
        LedMode = LED_MODE_EDIT;
    }

    if(LedMode == LED_MODE_RUNNING && !blockLeds) {
        /* In running mode, regularly update LEDs */
        discardNextIrSignal = true;
        updateLeds();
        led.show();
        blockLeds = true;
    }
}
