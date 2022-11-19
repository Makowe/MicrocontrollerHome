//
// Created by nicom on 15.03.2022.
//

#ifndef TEST3_COLOR_H
#define TEST3_COLOR_H


class Color {
public:
    Color(unsigned int red, unsigned int green, unsigned int blue) :
    red(red), green(green), blue(blue) {}

    explicit Color(unsigned int colors[3]) :
    red(colors[0]), green(colors[1]), blue(colors[2]) {}

    Color ModifyBrightness(unsigned int brightnessFactor, unsigned int factorMax) {
        red = red * brightnessFactor / factorMax;
        green = green * brightnessFactor / factorMax;
        blue = blue * brightnessFactor / factorMax;
        return *this;
    }

    unsigned int red;
    unsigned int green;
    unsigned int blue;
};


#endif//TEST3_COLOR_H
