//
// Created by nicom on 13.03.2021.
//

#include "LedInterface.h"
extern unsigned int GLOBAL_BRIGHTNESS;

LedInterface::LedInterface() {
    _pixels = Adafruit_NeoPixel(NUM_PIXELS, LED_OUT_PIN, NEO_GRB + NEO_KHZ800);
    this->begin();
}

void LedInterface::setColor(unsigned int number, unsigned int red,
                            unsigned int green, unsigned int blue) {

    unsigned long redMod = red * CORRECTION_RED * GLOBAL_BRIGHTNESS / NUM_BRIGHTNESS_LEVELS / CORRECTION_MAX;
    unsigned long greenMod = green * CORRECTION_GREEN * GLOBAL_BRIGHTNESS / NUM_BRIGHTNESS_LEVELS / CORRECTION_MAX;
    unsigned long blueMod = blue * CORRECTION_BLUE * GLOBAL_BRIGHTNESS / NUM_BRIGHTNESS_LEVELS / CORRECTION_MAX;

    _pixels.setPixelColor(number, redMod, greenMod, blueMod);

    if (number == 0 and DO_PRINT) {
        Serial.print("[LED INTER]: ");
        Serial.print("red: ");
        Serial.print(red);
        Serial.print(" ");
        Serial.print(redMod);
        Serial.print(", green: ");
        Serial.print(green);
        Serial.print(" ");
        Serial.print(greenMod);
        Serial.print(", blue: ");
        Serial.print(blue);
        Serial.print(" ");
        Serial.println(blueMod);
    }
}

void LedInterface::setColor(unsigned int number, Color color) {
    setColor(number, color.red, color.green, color.blue);
}

void LedInterface::begin() {
    _pixels.begin();
    _pixels.clear();
}

void LedInterface::clear() {
    _pixels.clear();
}

void LedInterface::show() {
    _pixels.show();
}
