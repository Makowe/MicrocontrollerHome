#include "LedInterface.h"
#include "theme/ThemeRainbow.h"
#include <Arduino.h>
#include <filter/FilterPulsate.h>

#include "../lib/Arduino-IRremote-3.9.0/Arduino-IRremote-3.9.0/src/TinyIRReceiver.hpp"


#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

LedInterface led;
int loop_iteration = 0;

//
// GLOBALS
//


ThemeRainbow rainbowTheme = ThemeRainbow(RAINBOW_DEFAULT_SPEED, RAINBOW_DEFAULT_COMPRESS);
Theme* theme = &rainbowTheme;

FilterPulsate filterPulsate = FilterPulsate(PULSATE_DEFAULT_SPEED);
Filter* filter = &filterPulsate;

volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;

unsigned int GLOBAL_BRIGHTNESS = 3;


void update_leds() {
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

    pinMode(BUTTON1_IN, INPUT_PULLUP);

    if(!initPCIInterruptForTinyReceiver()){
        Serial.println(F("No interrupt available for pin " STR(IR_INPUT_PIN))); // optimized out by the compiler, if not required :-)
    }
    Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_INPUT_PIN)));
}

bool buttonPressedOld = false;

bool button1PressedNew() {
    bool buttonPressed = !digitalRead(BUTTON1_IN);
    bool result;
    result = buttonPressed && !buttonPressedOld;
    buttonPressedOld = buttonPressed;
    return result;
}


void loop() {
    if(button1PressedNew()) {
        theme->nextSubTheme();
    }

    GLOBAL_BRIGHTNESS = analogRead(A0) / (1024 / NUM_BRIGHTNESS_LEVELS);
    if (sCallbackData.justWritten)
    {
        sCallbackData.justWritten = false;
        Serial.print(F("Address=0x"));
        Serial.print(sCallbackData.Address, HEX);
        Serial.print(F(" Command=0x"));
        Serial.print(sCallbackData.Command, HEX);
        if (sCallbackData.isRepeat)
        {
            Serial.print(F(" Repeat"));
        }
        Serial.println();
    }

    update_leds();
    led.show();
    delay(50);

}

/*
 * This is the function is called if a complete command was received
 * It runs in an ISR context with interrupts enabled, so functions like delay() etc. are working here
 */
#if defined(ESP8266) || defined(ESP32)
void IRAM_ATTR handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
#else
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
#endif
{

#if defined(ARDUINO_ARCH_MBED) || defined(ESP32)
    // Copy data for main loop, this is the recommended way for handling a callback :-)
    sCallbackData.Address = aAddress;
    sCallbackData.Command = aCommand;
    sCallbackData.isRepeat = isRepeat;
    sCallbackData.justWritten = true;
#else
    /*
     * This is not allowed in ISR context for any kind of RTOS
     * For Mbed we get a kernel panic and "Error Message: Semaphore: 0x0, Not allowed in ISR context" for Serial.print()
     * for ESP32 we get a "Guru Meditation Error: Core  1 panic'ed" (we also have an RTOS running!)
     */
    // Print only very short output, since we are in an interrupt context and do not want to miss the next interrupts of the repeats coming soon
    Serial.print(F("A=0x"));
    Serial.print(aAddress, HEX);
    Serial.print(F(" C=0x"));
    Serial.print(aCommand, HEX);
    Serial.print(F(" R="));
    Serial.print(isRepeat);
    Serial.println();
#endif
}
