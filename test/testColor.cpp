//
// Created by nicom on 12/22/2022.
//

#include "model/color.h"

#include <unity.h>

void setUp() {
    // set stuff up here
}

void tearDown() {
    // clean stuff up here
}

void testColor() {
    Color c1 = Color(0, 128, 255);
    TEST_ASSERT_EQUAL(c1.red, 0);
    TEST_ASSERT_EQUAL(c1.green, 128);
    TEST_ASSERT_EQUAL(c1.blue, 255);

    c1.modifyBrightness(4, 16);
    TEST_ASSERT_EQUAL(c1.red, 0);
    TEST_ASSERT_EQUAL(c1.green, 32);
    TEST_ASSERT_EQUAL(c1.blue, 63);

    Color c2 = Color(0, 128, 255);
    c2.modifyBrightness(255, 255);
    TEST_ASSERT_EQUAL(c2.red, 0);
    TEST_ASSERT_EQUAL(c2.green, 128);
    TEST_ASSERT_EQUAL(c2.blue, 255);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(testColor);
    UNITY_END();
}
