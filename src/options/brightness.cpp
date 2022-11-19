//
// Created by nicom on 19.11.2022.
//

#include "brightness.h"
#include <Arduino.h>

unsigned int brightness_level = 3;

void changeBrightness(bool increase) {
    if(increase && brightness_level < NUM_BRIGHTNESS_LEVELS-1) { brightness_level += 1; }
    if(!increase && brightness_level > 0) { brightness_level -= 1; }
    Serial.print("Set brightness to level: ");
    Serial.print(brightness_level);
    Serial.print(", value: ");
    Serial.println(brightness);
}