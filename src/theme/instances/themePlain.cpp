//
// Created by nicom on 12/14/2022.
//

#include "themePlain.h"
Color ThemePlain::calcTheme(unsigned int pixel_idx) {
    return _subThemeColors[_currentSubTheme];
}

void ThemePlain::nextTick() {
}
