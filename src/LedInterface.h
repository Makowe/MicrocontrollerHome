//
// Created by nicom on 13.03.2021.
//


#ifndef TEST3_LEDINTERFACE_H
#define TEST3_LEDINTERFACE_H

#include <Adafruit_NeoPixel.h>
#include "constants.h"

/*
 * wrapper class for AdaFruit NeonPixel object with additional methods.
 */
class LedInterface {
public:

    LedInterface();

    void setColor(unsigned int number, unsigned int red, unsigned int green, unsigned int blue);
    void setColor(unsigned int number, Color color);
    void begin();
    void clear();
    void show();

private:
    Adafruit_NeoPixel _pixels;
};


#endif //TEST3_LEDINTERFACE_H
