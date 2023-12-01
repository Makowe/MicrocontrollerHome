//
// Created by nicom on 19.11.2022.
//

#include <Arduino.h>

#include "brightness.h"
#include "debug.h"


unsigned int brightnessLevel = 3;

void changeBrightness(uint8_t direction) {
    if(direction == BRIGHTNESS_INCREASE && brightnessLevel < NUM_BRIGHTNESS_LEVELS-1) { brightnessLevel += 1; }
    if(direction == BRIGHTNESS_DECREASE && brightnessLevel > 0) { brightnessLevel -= 1; }
    RUN_DEBUG_FUNCTION(
            DEBUG_REMOTE,
            {
                Serial.print("Set brightnessVal to level: ");
                Serial.print(brightnessLevel);
                Serial.print(", value: ");
                Serial.println(brightnessVal);
            }
    );
}