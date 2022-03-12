#include "LedInterface.h"
#include "Rainbow.h"
#include "constants.h"
#include <Arduino.h>

LedInterface led;

unsigned int GLOBAL_BRIGHTNESS = 3;
unsigned int rainbowPosition = 0;
unsigned int RAINBOW_SPEED = 4;
unsigned int RAINBOW_COMPRESS = 4;


unsigned int pulse_old = 16;
unsigned int pulse_new = 16;
unsigned int pulse_fade = 16;
unsigned int pulse_period = 0;

void setup() {

    Serial.begin(9600);
}

void update_rainbow() {
    if (rainbowPosition >= RAINBOW_LENGTH) {
        rainbowPosition = 0;
    }
    else {
        rainbowPosition += RAINBOW_SPEED;
    }

    for (unsigned int led_idx = 0; led_idx < NUM_PIXELS; led_idx++) {
        Color color = Rainbow::calcRainbowColor(rainbowPosition + (led_idx * RAINBOW_COMPRESS));
        led.setColor(led_idx, color);
    }
}

void loop() {
    if (pulse_fade == pulse_new) {
        pulse_old = pulse_new;
        pulse_new = rand() % (PULSE_MAX - PULSE_MIN) + (PULSE_MIN);
    }
    if (pulse_period >= PULSE_NUM_PERIODS) {
        pulse_fade = pulse_fade + (pulse_new > pulse_old) - (pulse_new < pulse_old);
        pulse_period = 0;
    }
    else {
        pulse_period += 1;
    }

    pulse_fade = 0;
    update_rainbow();
    led.show();
    delay(50);
}
