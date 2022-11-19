//
// Created by nicom on 04.11.2022.
//

#include "remote.h"
#include "brightness.h"
#include "constants.h"
#include <Arduino.h>

void buttonClicked(uint16_t button) {
    switch (button) {
        case IR_BUTTON_UP:
            changeBrightness(true);
            break;
        case IR_BUTTON_DOWN:
            changeBrightness(false);
            break;
        case IR_BUTTON_OK:
            tooglePause();
            break;
        case IR_BUTTON_RIGHT:
            changeFilter(true);
            break;
        case IR_BUTTON_LEFT:
            changeFilter(false);
        case IR_BUTTON_0:
            setTheme(0);
            break;
        case IR_BUTTON_1:
            setTheme(1);
            break;
        default:
            break;
    }
}




void changeFilter(bool forward) { }
void setTheme(int theme) { }
void tooglePause() { }

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