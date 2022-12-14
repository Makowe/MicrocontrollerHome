//
// Created by nicom on 12/14/2022.
//

#ifndef TEST3_THEMEPLAIN_H
#define TEST3_THEMEPLAIN_H


#include "../theme.h"

#define PLAIN_SUB_THEMES 7

class ThemePlain : public Theme {
public:

    explicit ThemePlain() = default;
    Color calcTheme(unsigned int pixel_idx) override;
    void nextSubTheme() override {
            _currentSubTheme >= PLAIN_SUB_THEMES - 1 ? _currentSubTheme = 0 : _currentSubTheme+=1;
    };
    void previousSubTheme() override {
            _currentSubTheme == 0 ? _currentSubTheme = PLAIN_SUB_THEMES - 1 : _currentSubTheme-=1;
    };
    void nextTick() override;

    Theme* nextTheme = nullptr;

private:
    unsigned int _currentSubTheme = 0;
    Color _subThemeColors[PLAIN_SUB_THEMES] = {
            {255, 255, 255},
            {255, 0, 0},
            {200, 200, 0},
            {0, 255, 0},
            {0, 200, 200},
            {0, 0, 255},
            {200, 0, 255}
    };

};


#endif//TEST3_THEMEPLAIN_H
