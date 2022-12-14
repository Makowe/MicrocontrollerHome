//
// Created by nicom on 04.11.2022.
//

#ifndef TEST3_REMOTE_H
#define TEST3_REMOTE_H

#include "debug.h"
#include <stdint.h>

#if DEBUG_REMOTE
#include <Arduino.h>
#endif



#define IR_BUTTON_2 0x46
#define IR_BUTTON_3 0x47
#define IR_BUTTON_4 0x44
#define IR_BUTTON_1 0x45
#define IR_BUTTON_5 0x40
#define IR_BUTTON_6 0x43
#define IR_BUTTON_7 0x7
#define IR_BUTTON_8 0x15
#define IR_BUTTON_9 0x9
#define IR_BUTTON_0 0x19
#define IR_BUTTON_HASH 0xD
#define IR_BUTTON_STAR 0x16
#define IR_BUTTON_UP 0x18
#define IR_BUTTON_DOWN 0x52
#define IR_BUTTON_LEFT 0x8
#define IR_BUTTON_RIGHT 0x5A
#define IR_BUTTON_OK 0x1C

#define IR_BUTTON_HOLD_DELAY 3
#define IR_BLOCK_DELAY_AFTER_EDIT 5

#if DEBUG_REMOTE

#define IR_BUTTON_2_NAME "2"
#define IR_BUTTON_3_NAME "3"
#define IR_BUTTON_4_NAME "4"
#define IR_BUTTON_1_NAME "1"
#define IR_BUTTON_5_NAME "5"
#define IR_BUTTON_6_NAME "6"
#define IR_BUTTON_7_NAME "7"
#define IR_BUTTON_8_NAME "8"
#define IR_BUTTON_9_NAME "9"
#define IR_BUTTON_0_NAME "0"
#define IR_BUTTON_HASH_NAME "#"
#define IR_BUTTON_STAR_NAME "*"
#define IR_BUTTON_UP_NAME "/\\"
#define IR_BUTTON_DOWN_NAME "\\/"
#define IR_BUTTON_LEFT_NAME "<-"
#define IR_BUTTON_RIGHT_NAME "->"
#define IR_BUTTON_OK_NAME "OK"

struct ButtonToName {
    uint16_t value;
    char name[4];
};

constexpr ButtonToName buttonNames[] {
        {IR_BUTTON_2, IR_BUTTON_2_NAME},
        {IR_BUTTON_3, IR_BUTTON_3_NAME},
        {IR_BUTTON_4, IR_BUTTON_4_NAME},
        {IR_BUTTON_1, IR_BUTTON_1_NAME},
        {IR_BUTTON_5, IR_BUTTON_5_NAME},
        {IR_BUTTON_6, IR_BUTTON_6_NAME},
        {IR_BUTTON_7, IR_BUTTON_7_NAME},
        {IR_BUTTON_8, IR_BUTTON_8_NAME},
        {IR_BUTTON_9, IR_BUTTON_9_NAME},
        {IR_BUTTON_0, IR_BUTTON_0_NAME},
        {IR_BUTTON_HASH, IR_BUTTON_HASH_NAME},
        {IR_BUTTON_STAR, IR_BUTTON_STAR_NAME},
        {IR_BUTTON_UP, IR_BUTTON_UP_NAME},
        {IR_BUTTON_DOWN, IR_BUTTON_DOWN_NAME},
        {IR_BUTTON_LEFT, IR_BUTTON_LEFT_NAME},
        {IR_BUTTON_RIGHT, IR_BUTTON_RIGHT_NAME},
        {IR_BUTTON_OK, IR_BUTTON_OK_NAME},
};

#endif

void buttonClicked(uint16_t button);

#if DEBUG_REMOTE
void print_detected_button(uint16_t button, bool repetition = false);
#endif

#endif//TEST3_REMOTE_H
