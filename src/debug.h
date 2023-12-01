//
// Created by nicom on 19.11.2022.
//

#ifndef TEST3_DEBUG_H
#define TEST3_DEBUG_H

#include <Arduino.h>

#define DEBUG_LEDS 1
#define DEBUG_MAIN 1
#define DEBUG_REMOTE 1
#define DEBUG_FILTER 1

#define RUN_DEBUG_FUNCTION(channel, func) { if(channel) {func; } }
#define PRINT_DEBUG_MSG(channel, msg) { if(channel) {printDebugMsg(msg); } }

inline void printDebugMsg(const String& msg) {
    Serial.println(msg);
}

inline void printDebugMsg(int msg) {
    Serial.println(msg);
}



#endif//TEST3_DEBUG_H