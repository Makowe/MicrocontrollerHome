#include "LedInterface.h"
#include "theme/ThemeRainbow.h"
#include <Arduino.h>
#include <filter/FilterPulsate.h>
#include <IRremote.h>
#include <TinyIRReceiver.hpp>


LedInterface led;
volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;
int loop_iteration = 0;

//
// GLOBALS
//

ThemeRainbow rainbowTheme = ThemeRainbow(RAINBOW_DEFAULT_SPEED, RAINBOW_DEFAULT_COMPRESS);
Theme* theme = &rainbowTheme;

FilterPulsate filterPulsate = FilterPulsate(PULSATE_DEFAULT_SPEED);
Filter* filter = &filterPulsate;

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
    initPCIInterruptForTinyReceiver();

    pinMode(BUTTON1_IN, INPUT_PULLUP);
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
        Serial.print("Address=0x");
        Serial.print(sCallbackData.Address, HEX);
        Serial.print(" Command=0x");
        Serial.print(sCallbackData.Command, HEX);
        if (sCallbackData.isRepeat)
        {
            Serial.print(" Repeat");
        }
        Serial.println();
    }

    update_leds();
    led.show();
    delay(50);

}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
{
    if(!isRepeat) {
        sCallbackData.Address = aAddress;
        sCallbackData.Command = aCommand;
        sCallbackData.isRepeat = isRepeat;
        sCallbackData.justWritten = true;
    }
}