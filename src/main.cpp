#include <Arduino.h>
#include "constants.h"
#include "LedInterface.h"
#include "Rainbow.h"

LedInterface led;

unsigned int GLOBAL_BRIGHTNESS = 4;
unsigned int rainbowPosition = 0;
unsigned int RAINBOW_SPEED = 1;
unsigned int RAINBOW_COMPRESS = 1;
bool do_update = false;

void setup() {
    // set Timer1 mode to CTC (Clear on match with Output Compare A)
    // and prescale to 1024
    TCCR1B = 0b1101;

    // Output Compare Value
    OCR1A = 5000;

    // Enable interrupt when Timer Value == Input Capture Value
    TIMSK1 = 0b10;
    TIFR1 |= (1 << OCF1A);
    Serial.begin(9600);
}

void update_rainbow() {
    if(rainbowPosition >= RAINBOW_LENGTH) {
        rainbowPosition = 0; }
    else  {
        rainbowPosition += RAINBOW_SPEED; }

    for(unsigned  int i = 0; i < NUM_PIXELS; i++){
        Color color = Rainbow::calcRainbowColor(rainbowPosition + (i * RAINBOW_COMPRESS));
        led.setColor(i, color);
    }
}

void loop() {
    if(do_update) {
        update_rainbow();
        led.show();
        do_update = false;
    }
}

ISR(TIMER1_COMPA_vect) {
    do_update = true;
    TIFR1 = 0;
}