#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-redundant-declaration"
//
// Created by nicom on 14.07.2021.
//

#include "themeRainbow.h"

constexpr unsigned int ThemeRainbow::base_values[RAINBOW_SUB_THEMES][3][RAINBOW_SECTIONS];

ThemeRainbow::ThemeRainbow(unsigned int speed, unsigned int compress) : speed(speed), compress(compress) {}

Color ThemeRainbow::calcTheme(unsigned int pixel_idx) {
    unsigned int rainbowPosition = (this->position + (pixel_idx * this->compress)) % RAINBOW_LENGTH;

    unsigned int sectionNumber = rainbowPosition / RAINBOW_WIDTH_SECTION;
    unsigned int posInSection = rainbowPosition % RAINBOW_WIDTH_SECTION;
    return ThemeRainbow::getSectionColor(sectionNumber, posInSection);
}

void ThemeRainbow::nextTick() {
    this->position += this->speed;
    this->position = this->position % RAINBOW_LENGTH;
}

Color ThemeRainbow::getSectionColor(unsigned int section, unsigned int posInSection) const {
    unsigned int result_color[3] = {0, 0, 0};
    for(int color = 0; color < 3; color++) {
        unsigned int baseValueBefore = getBaseBefore(color, section);
        unsigned int baseValueAfter = getBaseAfter(color, section);

        if(posInSection < RAINBOW_WIDTH_SOLO) {
            result_color[color] = baseValueBefore;
        }
        else {
            result_color[color] = interpolate(baseValueBefore, baseValueAfter,
                                              posInSection-RAINBOW_WIDTH_SOLO, RAINBOW_WIDTH_FADE);
        }
    }
    return Color(result_color);
}

unsigned int ThemeRainbow::getBaseBefore(unsigned int color, unsigned int section) const {
    return base_values[subTheme][color][section];
}

unsigned int ThemeRainbow::getBaseAfter(unsigned int color, unsigned int section) const {
    if(section + 1 < RAINBOW_SECTIONS) {
        return base_values[subTheme][color][section+1];
    }
    else {
        return base_values[subTheme][color][0];
    }
}
unsigned int ThemeRainbow::interpolate(unsigned int valueLeft, unsigned int valueRight, unsigned int position, unsigned int maxPosition) {
    if(valueLeft == valueRight) {
        return valueLeft;
    }
    else if(valueLeft < valueRight){
        return position * (valueRight - valueLeft) / maxPosition + valueLeft;
    }
    else {
        return (maxPosition - position) * (valueLeft - valueRight) / maxPosition + valueRight;
    }
}


#pragma clang diagnostic pop