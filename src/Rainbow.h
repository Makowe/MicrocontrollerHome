//
// Created by nicom on 14.07.2021.
//

#ifndef TEST3_RAINBOW_H
#define TEST3_RAINBOW_H

#include "constants.h"

class Rainbow {
public:
    static Color getSectionColor(unsigned int section, unsigned int posInSection);
    static Color calcRainbowColor(unsigned int position);

    constexpr static unsigned int high_color[6] = {
            RED, GREEN, GREEN, BLUE, BLUE, RED};
    constexpr static unsigned int fade_color[6] = {
            GREEN, RED, BLUE, GREEN, RED, BLUE};
    constexpr static bool fade_upwards[6] = {
            true, false, true, false, true, false};
};

#endif// TEST3_RAINBOW_H
