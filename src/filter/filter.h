//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_FILTER_H
#define TEST3_FILTER_H

#include "model/color.h"


class Filter {
public:
    virtual Color applyFilter(unsigned int pixel_idx, Color color) = 0;
    virtual void nextTick() = 0;

    Filter* nextFilter = nullptr;
};


#endif//TEST3_FILTER_H
