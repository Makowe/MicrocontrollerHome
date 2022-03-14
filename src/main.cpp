#include "LedInterface.h"
#include "constants.h"
#include "theme/ThemeRainbow.h"
#include <Arduino.h>

LedInterface led;



//
// GLOBALS
//

ThemeRainbow rainbowTheme = ThemeRainbow(DEFAULT_RAINBOW_SPEED, DEFAULT_RAINBOW_COMPRESS);
Theme *theme = &rainbowTheme;

unsigned int GLOBAL_BRIGHTNESS = 3;


unsigned int pulse_old = 16;
unsigned int pulse_new = 16;
unsigned int pulse_fade = 16;
unsigned int pulse_period = 0;
unsigned int pulse_position = 0;



void update_leds() {
    theme->nextTick();

    for (unsigned int pixel_idx = 0; pixel_idx < NUM_PIXELS; pixel_idx++) {
        Color color = theme->calcTheme(pixel_idx);
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
