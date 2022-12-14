//
// Created by nicom on 12/14/2022.
//

#include "themeHandler.h"
#include <theme/instances/themePlain.h>
#include <theme/instances/themeRainbow.h>

ThemeRainbow themeRainbow = ThemeRainbow(RAINBOW_DEFAULT_SPEED, RAINBOW_DEFAULT_COMPRESS);
ThemePlain themePlain = ThemePlain();

Theme* currentTheme = &themeRainbow;

void initThemes() {
    themeRainbow.nextTheme = &themePlain;
    themePlain.nextTheme = &themeRainbow;
}

void selectNextTheme() {
    currentTheme = currentTheme->nextTheme;
}
