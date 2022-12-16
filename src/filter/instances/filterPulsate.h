//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_FILTERPULSATE_H
#define TEST3_FILTERPULSATE_H

#include "filter/filter.h"
#include "model/color.h"
#include "constants.h"

// pulsating
#define PULSATE_LENGTH 25
#define PULSATE_MAX 255
#define PULSATE_MIN 64

#define PULSATE_DEFAULT_SPEED 1
#define PULSATE_ARRAY_SIZE (NUM_PIXELS/PULSATE_LENGTH + 3)


class FilterPulsate : public Filter {
public:
    explicit FilterPulsate(unsigned int speed);
    Color applyFilter(unsigned int pixel_idx, Color color) override;
    void nextTick() override;

private:
    void calc_next_level();
    void init_levels();
    unsigned int interpolate(unsigned int section, unsigned int positionInSection);

    unsigned int position = 0;
    unsigned int speed;

    unsigned int levels[PULSATE_ARRAY_SIZE]{};
};


#endif//TEST3_FILTERPULSATE_H
