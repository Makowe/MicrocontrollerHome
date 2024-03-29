//
// Created by nicom on 14.03.2022.
//

#ifndef TEST3_THEME_H
#define TEST3_THEME_H

#include <model/color.h>


class Theme {
public:
    virtual Color calcTheme(unsigned int pixel_idx) = 0;
    virtual void nextSubTheme() = 0;
    virtual void previousSubTheme() = 0;
    virtual void nextTick() = 0;

    Theme* nextTheme = nullptr;
};


#endif//TEST3_THEME_H
