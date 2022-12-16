//
// Created by nicom on 12/14/2022.
//

#ifndef TEST3_FILTERNOTHING_H
#define TEST3_FILTERNOTHING_H

#include "filter/filter.h"


class FilterNothing : public Filter {

public:
    explicit FilterNothing() = default;
    Color applyFilter(unsigned int pixel_idx, Color color) override;
    void nextTick() override {};

};


#endif//TEST3_FILTERNOTHING_H
