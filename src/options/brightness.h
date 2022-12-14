//
// Created by nicom on 19.11.2022.
//

#ifndef TEST3_BRIGHTNESS_H
#define TEST3_BRIGHTNESS_H

/******************************************************************************
 * Correction of brightnessVal between red, green and blue
 *****************************************************************************/

#define CORRECTION_DENOMINATOR 16

#define CORRECTION_RED 16
#define CORRECTION_GREEN 10
#define CORRECTION_BLUE 6

/******************************************************************************
 * global brightnessVal setting
 *****************************************************************************/

#define BRIGHTNESS_DENOMINATOR 64

extern unsigned int brightnessLevel;
constexpr unsigned int brightnessLevels[] = {
        0, 1, 2, 4, 6, 10, 15, 25, 40, 64
};

#define NUM_BRIGHTNESS_LEVELS sizeof(brightnessLevels)/sizeof(brightnessLevels[0])
#define brightnessVal brightnessLevels[brightnessLevel]

void changeBrightness(bool increase);

#endif//TEST3_BRIGHTNESS_H
