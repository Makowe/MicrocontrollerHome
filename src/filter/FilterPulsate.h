//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_FILTERPULSATE_H
#define TEST3_FILTERPULSATE_H

#include "constants.h"
#include <Color.h>
#include <filter/Filter.h>
#include "HardwareSerial.h"

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
