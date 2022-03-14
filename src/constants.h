//Pins

#ifndef TEST3_CONSTANTS_H
#define TEST3_CONSTANTS_H

#include "Global.h"

//debug
#define DO_PRINT 1


// pins
#define LED_OUT 3
#define POTI_IN "A0"


//constants
#define NUM_PIXELS 196
#define NUM_BRIGHTNESS_LEVELS 16

#define CORRECTION_RED 16
#define CORRECTION_GREEN 10
#define CORRECTION_BLUE 6

#define RED 0
#define GREEN 1
#define BLUE 2

// the brightness gets multiplied by a factor [1:16] and divided by 16 to reduce brightness.
#define CORRECTION_MAX 16

//rainbow
#define RAINBOW_WIDTH_FADE Global::rainbow_fade_width
#define RAINBOW_WIDTH_SOLO (256 - RAINBOW_WIDTH_FADE)
#define RAINBOW_WIDTH_SECTION 256
#define RAINBOW_SECTIONS 6
#define RAINBOW_LENGTH (RAINBOW_WIDTH_SECTION * RAINBOW_SECTIONS)

#define DEFAULT_RAINBOW_SPEED 4
#define DEFAULT_RAINBOW_COMPRESS 4

// pulsating
#define PULSATE_LENGTH 100
#define PULSATE_LEVELS 16
#define PULSE_MAX 16
#define PULSE_MIN 8

struct Color {

    Color(unsigned int red, unsigned int green, unsigned int blue) {
        _red = red;
        _green = green;
        _blue = blue;
    }

    explicit Color(unsigned int colors[3]) {
        _red = colors[0];
        _green = colors[1];
        _blue = colors[2];
    }

    unsigned int _red;
    unsigned int _green;
    unsigned int _blue;
};

#endif//TEST3_CONSTANTS_H