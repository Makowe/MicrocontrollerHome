#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-redundant-declaration"
//
// Created by nicom on 14.07.2021.
//

#include "ThemeRainbow.h"

constexpr unsigned int ThemeRainbow::high_color[];
constexpr unsigned int ThemeRainbow::fade_color[];
constexpr bool ThemeRainbow::fade_upwards[];

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

Color ThemeRainbow::getSectionColor(unsigned int section, unsigned int posInSection) {
    unsigned int colors[3] = {0, 0, 0};

    unsigned int color_high = ThemeRainbow::high_color[section];
    colors[color_high] = 255;

    unsigned int color_fade = ThemeRainbow::fade_color[section];
    unsigned int value_fade;

    if (posInSection < RAINBOW_WIDTH_SOLO) {
        value_fade = 255 * !ThemeRainbow::fade_upwards[section];
    }
    else {
        unsigned int posInFade = posInSection - RAINBOW_WIDTH_SOLO;
        if (ThemeRainbow::fade_upwards[section]) {
            value_fade = posInFade * 256 / RAINBOW_WIDTH_FADE;
        }
        else {
            value_fade = (RAINBOW_WIDTH_FADE - posInFade -1) * 256 / RAINBOW_WIDTH_FADE;
        }
    }
    colors[color_fade] = value_fade;

    return Color(colors);
}
#pragma clang diagnostic pop