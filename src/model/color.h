//
// Created by nicom on 15.03.2022.
//

#ifndef TEST3_COLOR_H
#define TEST3_COLOR_H

#include <stdint.h>

class Color {
public:
    Color(uint8_t red, uint8_t green, uint8_t blue) :
    red(red), green(green), blue(blue) {}

    Color modifyBrightness(uint8_t brightnessFactor, uint8_t factorMax) {
        red = red * brightnessFactor / factorMax;
        green = green * brightnessFactor / factorMax;
        blue = blue * brightnessFactor / factorMax;
        return *this;
    }

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};


#endif//TEST3_COLOR_H
