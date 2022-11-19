//
// Created by nicom on 14.07.2021.
//

#ifndef TEST3_THEMERAINBOW_H
#define TEST3_THEMERAINBOW_H

//rainbow
#define RAINBOW_WIDTH_FADE 128
#define RAINBOW_WIDTH_SOLO (256 - RAINBOW_WIDTH_FADE)
#define RAINBOW_WIDTH_SECTION 256
#define RAINBOW_SECTIONS 6
#define RAINBOW_LENGTH (RAINBOW_WIDTH_SECTION * RAINBOW_SECTIONS)
#define RAINBOW_SUB_THEMES 4

#define RAINBOW_DEFAULT_SPEED 2
#define RAINBOW_DEFAULT_COMPRESS 4

#include "theme.h"
#include <model/color.h>

class ThemeRainbow : public Theme {
public:
    ThemeRainbow(unsigned int speed, unsigned int compress);
    Color calcTheme(unsigned int rainbow_position) override;
    void nextTick() override;

    void nextSubTheme() override {
        subTheme + 1 == RAINBOW_SUB_THEMES ? subTheme = 0 : subTheme+=1;
    }
    unsigned int getBaseBefore(unsigned int color, unsigned int section) const;
    unsigned int getBaseAfter(unsigned int color, unsigned int section) const;
    static unsigned int interpolate(unsigned int valueLeft, unsigned int valueRight, unsigned int position, unsigned int maxPosition);

private:
    Color getSectionColor(unsigned int section, unsigned int posInSection) const;

    unsigned int position = 0;
    unsigned int speed;
    unsigned int compress;
    unsigned int subTheme = 0;

    constexpr static unsigned int base_values[RAINBOW_SUB_THEMES][3][RAINBOW_SECTIONS] = {
            {
                    // https://coolors.co/ff0000-ffff00-00ff00-00ffff-0000ff-ff00ff
                    {255, 255, 0, 0, 0, 255},
                    {0, 255, 255, 255, 0, 0},
                    {0, 0, 0, 255, 255, 255}
            },
            {
                    // https://coolors.co/a31621-db7f8e-d200c0-ff2424-933fa0-d8d8f6
                    {163, 219, 210, 255, 147, 216},
                    {22, 127, 0, 36, 63, 216},
                    {33, 142, 192, 36, 160, 246}
            },
            {
                    //https://coolors.co/a31621-db7f8e-e8e9eb-5e747f-933fa0-c8c8ff
                    {163, 219, 232, 94, 147, 200},
                    {22, 127, 233, 116, 63, 200},
                    {33, 142, 235, 127, 160, 255}
            },
            {
                    // https://coolors.co/07c8a7-00b7e6-a9adb4-94fa9a-e1e27b-e9acaf
                    {7, 0, 169, 148, 225, 233},
                    {200, 183, 173, 250, 226, 172},
                    {167, 230, 180, 154, 123, 175}
            }

    };
};

#endif// TEST3_THEMERAINBOW_H
