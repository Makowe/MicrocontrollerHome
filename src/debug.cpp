//
// Created by nicom on 19.11.2022.
//

#include "debug.h"

void PRINT_DEBUG_MSG(unsigned int channel, const String& msg, unsigned int new_line) {
    if(channel) {
        if(new_line == NEW_LINE_AFTER) {
            Serial.println(msg);
        }
        else {
            Serial.print(msg);
        }
    }
}

void PRINT_DEBUG_MSG(unsigned int channel, int msg, unsigned int new_line) {
    if(channel) {
        if(new_line == NEW_LINE_AFTER) {
            Serial.println(msg);
        }
        else {
            Serial.print(msg);
        }
    }
}
