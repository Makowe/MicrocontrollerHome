//
// Created by nicom on 14.07.2021.
//

#ifndef TEST3_THEMERAINBOW_H
#define TEST3_THEMERAINBOW_H

#include "Theme.h"
#include "constants.h"
#include <Color.h>

class ThemeRainbow : public Theme {
public:
    ThemeRainbow(unsigned int speed, unsigned int compress);
    Color calcTheme(unsigned int rainbow_position) override;
    void nextTick() override;
    static unsigned int getBaseBefore(unsigned int color, unsigned int section);
    static unsigned int getBaseAfter(unsigned int color, unsigned int section);
    static unsigned int interpolate(unsigned int valueLeft, unsigned int valueRight, unsigned int position, unsigned int maxPosition);

private:
    static Color getSectionColor(unsigned int section, unsigned int posInSection);

    unsigned int position = 0;
    unsigned int speed;
    unsigned int compress;

    constexpr static unsigned int base_values[3][6] = {
            {255, 255, 0, 0, 0, 255},
            {0, 255, 255, 255, 0, 0},
            {0, 0, 0, 255, 255, 255}
    };
};

#endif// TEST3_THEMERAINBOW_H
