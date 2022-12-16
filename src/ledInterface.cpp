//
// Created by nicom on 13.03.2021.
//

#include "ledInterface.h"
#include "debug.h"
#include "options/brightness.h"


uint8_t LedMode = LED_MODE_RUNNING;

LedInterface::LedInterface() {
    _pixels = Adafruit_NeoPixel(NUM_PIXELS, LED_OUT_PIN, NEO_GRB + NEO_KHZ800);
    this->begin();
}

void LedInterface::setColor(unsigned int number, unsigned int red,
                            unsigned int green, unsigned int blue) {

    unsigned long redMod = red * BRIGHTNESS_CORRECTION_RED * brightnessVal / BRIGHTNESS_CORRECTION_DENOMINATOR / BRIGHTNESS_LEVEL_DENOMINATOR;
    unsigned long greenMod = green * BRIGHTNESS_CORRECTION_GREEN * brightnessVal / BRIGHTNESS_CORRECTION_DENOMINATOR / BRIGHTNESS_LEVEL_DENOMINATOR;
    unsigned long blueMod = blue * BRIGHTNESS_CORRECTION_BLUE * brightnessVal / BRIGHTNESS_CORRECTION_DENOMINATOR / BRIGHTNESS_LEVEL_DENOMINATOR;

    _pixels.setPixelColor(number, redMod, greenMod, blueMod);

    RUN_DEBUG_FUNCTION(
            DEBUG_LEDS,
            {
                if (number == 0) {
                    Serial.print("[LEDS]: ");
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
            });
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
