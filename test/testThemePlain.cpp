//
// Created by nicom on 12/22/2022.
//

#include "theme/instances/themePlain.h"

#include <unity.h>

void testThemePlain() {
    ThemePlain t1 = ThemePlain();
    Color cWhite = Color(255, 255, 255);
    Color cRed = Color(255, 0, 0);


    Color c = t1.calcTheme(0);
    TEST_ASSERT_EQUAL(cWhite.red, c.red);
    TEST_ASSERT_EQUAL(cWhite.green, c.green);
    TEST_ASSERT_EQUAL(cWhite.blue, c.blue);

    t1.nextSubTheme();
    c = t1.calcTheme(0);
    TEST_ASSERT_EQUAL(cRed.red, c.red);
    TEST_ASSERT_EQUAL(cRed.green, c.green);
    TEST_ASSERT_EQUAL(cRed.blue, c.blue);
}


