//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_THEME_H
#define TEST3_THEME_H

#include "constants.h"
#include <Color.h>


class Theme {
public:
    virtual Color calcTheme(unsigned int pixel_idx) = 0;
    virtual void nextTick() = 0;
};


#endif//TEST3_THEME_H
