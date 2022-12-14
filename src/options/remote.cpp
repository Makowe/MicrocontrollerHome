//
// Created by nicom on 04.11.2022.
//

#include "remote.h"
#include "brightness.h"
#include "constants.h"
#include <Arduino.h>
#include <filter/filterHandler.h>
#include <ledInterface.h>
#include <theme/themeHandler.h>

void buttonClicked(uint16_t button) {
    switch (button) {
        case IR_BUTTON_UP:
            changeBrightness(true);
            break;
        case IR_BUTTON_DOWN:
            changeBrightness(false);
            break;
        case IR_BUTTON_OK:
#if DEBUG_REMOTE
            Serial.println("[REMOTE]: Switch LedMode to running.");
#endif
            LedMode = LED_MODE_RUNNING;
            break;
        case IR_BUTTON_RIGHT:
            currentTheme->nextSubTheme();
            break;
        case IR_BUTTON_LEFT:
            currentTheme->previousSubTheme();
            break;
        case IR_BUTTON_STAR:
            selectNextTheme();
            Serial.println("[REMOTE]: Select next Theme");
            break;
        case IR_BUTTON_HASH:
            selectNextFilter();
            Serial.println("[REMOTE]: Select next Filter");
            break;
        default:
            break;
    }
}


#if DEBUG_REMOTE

void print_detected_button(uint16_t button, bool repetition) {
    Serial.print("[REMOTE]: Value ");
    Serial.print(button, HEX);
    for(auto buttonName : buttonNames) {
        if(buttonName.value == button) {
            Serial.print(", Detected Button ");
            Serial.print(buttonName.name);
            if(repetition) { Serial.print(" (Ignored due to repetition)"); }
            Serial.println();
            return;
        }
    }
    Serial.println(", No valid button detected");
}

#endif