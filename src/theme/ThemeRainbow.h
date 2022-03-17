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

private:
    static Color getSectionColor(unsigned int section, unsigned int posInSection);

    unsigned int position = 0;
    unsigned int speed;
    unsigned int compress;

    constexpr static unsigned int high_color[6] = {
            RED, GREEN, GREEN, BLUE, BLUE, RED};
    constexpr static unsigned int fade_color[6] = {
            GREEN, RED, BLUE, GREEN, RED, BLUE};
    constexpr static bool fade_upwards[6] = {
            true, false, true, false, true, false};
};

#endif// TEST3_THEMERAINBOW_H
