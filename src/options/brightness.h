//
// Created by nicom on 19.11.2022.
//

#ifndef TEST3_BRIGHTNESS_H
#define TEST3_BRIGHTNESS_H

/******************************************************************************
 * Correction of brightness between red, green and blue
 *****************************************************************************/

#define CORRECTION_DENOMINATOR 16

#define CORRECTION_RED 16
#define CORRECTION_GREEN 10
#define CORRECTION_BLUE 6

/******************************************************************************
 * global brightness setting
 *****************************************************************************/

#define BRIGHTNESS_DENOMINATOR 64

extern unsigned int brightness_level;
constexpr unsigned int brightness_levels[] = {
        0, 1, 2, 4, 6, 10, 15, 25, 40, 64
};

#define NUM_BRIGHTNESS_LEVELS sizeof(brightness_levels)/sizeof(brightness_levels[0])
#define brightness brightness_levels[brightness_level]

void changeBrightness(bool increase);

#endif//TEST3_BRIGHTNESS_H
