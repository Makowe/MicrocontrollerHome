//
// Created by nicom on 14.03.2022.
//

#include "filterPulsate.h"
#include <new>

Color FilterPulsate::applyFilter(unsigned int pixel_idx, Color color) {
    unsigned int positionOnFade = NUM_PIXELS-1 - pixel_idx + position;
    unsigned int section = positionOnFade / PULSATE_LENGTH;
    unsigned int positionInSection = positionOnFade % PULSATE_LENGTH;

    unsigned int brightness = interpolate(section, positionInSection);

    return color.ModifyBrightness(brightness, PULSATE_MAX);
}

unsigned int FilterPulsate::interpolate(unsigned int section, unsigned int positionInSection) {
    auto value_low = static_cast<long>(levels[section]);
    auto value_high = static_cast<long>(levels[section+1]);
    auto difference = value_high - value_low;
    auto interpolation = difference * positionInSection / PULSATE_LENGTH;
    return value_low + interpolation;
}

void FilterPulsate::nextTick() {
    position += speed;
    if(position >= PULSATE_LENGTH) {
        position = position % PULSATE_LENGTH;
        calc_next_level();
    }
}

FilterPulsate::FilterPulsate(unsigned int speed) : speed(speed) {
    init_levels();
}

void FilterPulsate::calc_next_level() {
    unsigned int last_level = levels[PULSATE_ARRAY_SIZE-1];
    unsigned int new_level;

    // make next level with 50% probability brighter and with 50% darker.
    unsigned int brighter = rand() % 2;

    if(brighter) {
        // clear special cases when modulo operation would result in undefined behaviour
        if(last_level == PULSATE_MAX) {new_level = PULSATE_MAX; }
        else { new_level = (rand() % (PULSATE_MAX - last_level)) + last_level; }
    }
    else {
        if (last_level == PULSATE_MIN) { new_level = PULSATE_MIN; }
        else { new_level = (rand() % (last_level - PULSATE_MIN)) + PULSATE_MIN; }
    }

    for(int i = 0; i < PULSATE_ARRAY_SIZE-1; i++) {
        levels[i] = levels[i+1];
    }
    levels[PULSATE_ARRAY_SIZE-1] = new_level;
#if DEBUG_FILTER
        Serial.print("[FILT PULS]:\t");
        Serial.print(levels[0]);
        Serial.print(' ');
        Serial.print(levels[1]);
        Serial.print(' ');
        Serial.print(levels[2]);
        Serial.print(' ');
        Serial.print(levels[3]);
        Serial.println(' ');
#endif
}

void FilterPulsate::init_levels() {
    for(unsigned int & level : levels) {
        unsigned int new_level = (rand() % (PULSATE_MAX - PULSATE_MIN)) + PULSATE_MIN;
        level = new_level;
    }
}


