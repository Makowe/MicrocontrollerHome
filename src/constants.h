//Pins

#ifndef TEST3_CONSTANTS_H
#define TEST3_CONSTANTS_H

#include "Global.h"

//debug
#define DO_PRINT 0


// pins
#define LED_OUT_PIN 3
#define IR_IN_PIN 2
#define POTI_IN "A0"


//constants
#define NUM_PIXELS 198
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

#define RAINBOW_DEFAULT_SPEED 2
#define RAINBOW_DEFAULT_COMPRESS 4

// pulsating
#define PULSATE_LENGTH 50
#define PULSATE_MAX 255
#define PULSATE_MIN 32

#define PULSATE_DEFAULT_SPEED 3

#define IR_INPUT_PIN 2

#endif//TEST3_CONSTANTS_H