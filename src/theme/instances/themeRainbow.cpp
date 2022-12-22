//
// Created by nicom on 14.07.2021.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-redundant-declaration"

#include "themeRainbow.h"

constexpr unsigned int ThemeRainbow::_base_values[RAINBOW_SUB_THEMES][3][RAINBOW_SECTIONS];

ThemeRainbow::ThemeRainbow(unsigned int speed, unsigned int compress) : _speed(speed), _compress(compress) {}

Color ThemeRainbow::calcTheme(unsigned int pixel_idx) {
    unsigned int rainbowPosition = (this->_position + (pixel_idx * this->_compress)) % RAINBOW_LENGTH;

    unsigned int sectionNumber = rainbowPosition / RAINBOW_WIDTH_SECTION;
    unsigned int posInSection = rainbowPosition % RAINBOW_WIDTH_SECTION;
    return ThemeRainbow::getSectionColor(sectionNumber, posInSection);
}

void ThemeRainbow::nextTick() {
    this->_position += this->_speed;
    this->_position = this->_position % RAINBOW_LENGTH;
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
    return Color(result_color[0], result_color[1], result_color[2]);
}

unsigned int ThemeRainbow::getBaseBefore(unsigned int color, unsigned int section) const {
    return _base_values[_currentSubTheme][color][section];
}

unsigned int ThemeRainbow::getBaseAfter(unsigned int color, unsigned int section) const {
    if(section + 1 < RAINBOW_SECTIONS) {
        return _base_values[_currentSubTheme][color][section+1];
    }
    else {
        return _base_values[_currentSubTheme][color][0];
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