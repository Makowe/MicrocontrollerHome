//
// Created by nicom on 19.11.2022.
//

#include "brightness.h"
#include <Arduino.h>

unsigned int brightnessLevel = 3;

void changeBrightness(bool increase) {
    if(increase && brightnessLevel < NUM_BRIGHTNESS_LEVELS-1) { brightnessLevel += 1; }
    if(!increase && brightnessLevel > 0) { brightnessLevel -= 1; }
    Serial.print("Set brightnessVal to level: ");
    Serial.print(brightnessLevel);
    Serial.print(", value: ");
    Serial.println(brightnessVal);
}