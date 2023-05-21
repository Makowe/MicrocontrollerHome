//
// Created by nicom on 04.11.2022.
//

#include <Arduino.h>

#include "remote.h"
#include "brightness.h"
#include "filter/filterHandler.h"
#include "ledInterface.h"
#include "theme/themeHandler.h"

bool processButtonClick(uint16_t button) {
    bool validButton = true;
    switch (button) {
        case IR_BUTTON_UP:
            changeBrightness(BRIGHTNESS_INCREASE);
            break;
        case IR_BUTTON_DOWN:
            changeBrightness(BRIGHTNESS_DECREASE);
            break;
        case IR_BUTTON_OK:
            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch LedMode to running.");
            LedMode = LED_MODE_RUNNING;
            break;
        case IR_BUTTON_RIGHT:
            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch to next subtheme.");
            currentTheme->nextSubTheme();
            break;
        case IR_BUTTON_LEFT:
            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch to previous subtheme.");
            currentTheme->previousSubTheme();
            break;
        case IR_BUTTON_STAR:
            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch to next theme.");
            selectNextTheme();
            Serial.println("[REMOTE]: Select next Theme");
            break;
        case IR_BUTTON_HASH:
            PRINT_DEBUG_MSG(DEBUG_REMOTE, "[REMOTE]: Switch to next filter.");
            selectNextFilter();
            Serial.println("[REMOTE]: Select next Filter");
            break;
        default:
            validButton = false;
            break;
    }
    return validButton;
}

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
