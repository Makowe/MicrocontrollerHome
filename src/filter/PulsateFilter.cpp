//
// Created by nicom on 14.03.2022.
//

#include "PulsateFilter.h"
#include <new>
Color PulsateFilter::calcFilter(unsigned int pixel_idx, Color color_without_filter) {
    return Color(0, 0, 0);
}

void PulsateFilter::nextTick() {
}

PulsateFilter::PulsateFilter(unsigned int speed, unsigned int pulsate) : speed(speed), pulsate(pulsate) {}

void PulsateFilter::calc_next_level() {
    unsigned int new_level = (rand() % (PULSE_MAX - PULSE_MIN)) + PULSE_MIN;
    for(int i = 0; i < PULSATE_ARRAY_SIZE-1; i++) {
        this->levels[i] = this->levels[i+1];
    }
    this->levels[PULSATE_ARRAY_SIZE-1] = new_level;
}

void PulsateFilter::init_levels() {
    for(unsigned int & level : this->levels) {
        unsigned int new_level = (rand() % (PULSE_MAX - PULSE_MIN)) + PULSE_MIN;
        level = new_level;
    }
}
