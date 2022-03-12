//
// Created by nicom on 14.07.2021.
//

#include "Rainbow.h"

constexpr unsigned int Rainbow::high_color[];
constexpr unsigned int Rainbow::fade_color[];
constexpr bool Rainbow::fade_upwards[];

Color Rainbow::getSectionColor(unsigned int section, unsigned int posInSection) {
    unsigned int colors[3] = {0, 0, 0};

    unsigned int color_high = Rainbow::high_color[section];
    colors[color_high] = 255;

    unsigned int color_fade = Rainbow::fade_color[section];
    unsigned int value_fade;

    if(posInSection < RAINBOW_WIDTH_SOLO) {
        value_fade = 255 * !Rainbow::fade_upwards[section];
    }
    else {
        unsigned int posInFade = posInSection - RAINBOW_WIDTH_SOLO;
        if(Rainbow::fade_upwards[section]) {
            value_fade = posInFade;
        }
        else {
            value_fade = 255 - posInFade;
        }
    }
    colors[color_fade] = value_fade;

    return Color(colors);
}


Color Rainbow::calcRainbowColor(unsigned int position) {
    position = position % RAINBOW_LENGTH;

    unsigned int sectionNumber = position / RAINBOW_WIDTH_SECTION;
    unsigned int posInSection = position % RAINBOW_WIDTH_SECTION;

    return Rainbow::getSectionColor(sectionNumber, posInSection);
}