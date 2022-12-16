//
// Created by nicom on 19.11.2022.
//

#ifndef TEST3_DEBUG_H
#define TEST3_DEBUG_H

#include <Arduino.h>

#define DEBUG_LEDS 1
#define DEBUG_MAIN 1
#define DEBUG_REMOTE 1
#define DEBUG_FILTER 0

#define NEW_LINE_AFTER 1
#define INLINE 0

#define RUN_DEBUG_FUNCTION(channel, func) {if(channel) {func; } }

void PRINT_DEBUG_MSG(unsigned int channel, const String& msg, unsigned int new_line=1);
void PRINT_DEBUG_MSG(unsigned int channel, int msg, unsigned int new_line=1);


#endif//TEST3_DEBUG_H