//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_PULSATEFILTER_H
#define TEST3_PULSATEFILTER_H

#include "constants.h"
#include <filter/Filter.h>

#define PULSATE_ARRAY_SIZE (NUM_PIXELS/PULSATE_LENGTH + 2)

class PulsateFilter : public Filter {
public:
    PulsateFilter(unsigned int speed, unsigned int pulsate);
    Color calcFilter(unsigned int pixel_idx, Color color_without_filter) override;
    void nextTick() override;

private:
    void calc_next_level();
    void init_levels();

    unsigned int current_position = 0;
    unsigned int speed;
    unsigned int pulsate;

    unsigned int levels[PULSATE_ARRAY_SIZE];
};


#endif//TEST3_PULSATEFILTER_H
