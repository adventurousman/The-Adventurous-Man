//
// Created by hoang on 12/9/15.
//
#include <cxxtest/TestSuite.h>
#include "../CApp.h"
#include "../CPlayer.h"
#include <iostream>

#ifndef THE_ADVENTUROUS_MAN_GAMETESTSUITE_H
#define THE_ADVENTUROUS_MAN_GAMETESTSUITE_H

class MyTestSuite1 : public CxxTest::TestSuite
{
public:
    void testSimple(void)
    {
        TS_ASSERT(1 + 1 > 1);
        TS_ASSERT_EQUALS(1 + 1, 2);
    }

    void testApplication(void)
    {
        CApp app;
        CPlayer* p = app.getPlayer();
        TS_ASSERT_EQUALS(p->getHealth(), 0);
    }
};
#endif //THE_ADVENTUROUS_MAN_GAMETESTSUITE_H
