//
// Created by nicom on 19.11.2022.
//

#ifndef TEST3_BRIGHTNESS_H
#define TEST3_BRIGHTNESS_H

#include <stdint.h>

#define BRIGHTNESS_CORRECTION_DENOMINATOR 16
#define BRIGHTNESS_CORRECTION_RED 16
#define BRIGHTNESS_CORRECTION_GREEN 10
#define BRIGHTNESS_CORRECTION_BLUE 6

#define BRIGHTNESS_DECREASE 0
#define BRIGHTNESS_INCREASE 1

#define BRIGHTNESS_LEVEL_DENOMINATOR 64


extern unsigned int brightnessLevel;
constexpr unsigned int brightnessLevels[] = {
        0, 1, 2, 4, 6, 10, 15, 25, 40, 64
};

#define NUM_BRIGHTNESS_LEVELS (sizeof(brightnessLevels)/sizeof(brightnessLevels[0]))
#define brightnessVal brightnessLevels[brightnessLevel]

void changeBrightness(uint8_t direction);

#endif//TEST3_BRIGHTNESS_H
