#include "LedInterface.h"
#include "theme/ThemeRainbow.h"
#include <Arduino.h>
#include <filter/FilterPulsate.h>
#include <IRremote.h>


LedInterface led;


//
// GLOBALS
//

ThemeRainbow rainbowTheme = ThemeRainbow(RAINBOW_DEFAULT_SPEED, RAINBOW_DEFAULT_COMPRESS);
Theme* theme = &rainbowTheme;

FilterPulsate filterPulsate = FilterPulsate(PULSATE_DEFAULT_SPEED);
Filter* filter = &filterPulsate;

unsigned int GLOBAL_BRIGHTNESS = 3;


void update_leds() {
    theme->nextTick();
    filter->nextTick();

    for (unsigned int pixel_idx = 0; pixel_idx < NUM_PIXELS; pixel_idx++) {
        Color color = theme->calcTheme(pixel_idx);
        color = filter->applyFilter(pixel_idx, color);
        led.setColor(pixel_idx, color);
    }
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    update_leds();
    led.show();
    delay(50);
}
