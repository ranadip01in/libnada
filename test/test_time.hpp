#pragma once

#include <doctest.h>
#include <nada/time.hpp>

class Test_time { TEST_CASE_CLASS("Test_time") {

    SUBCASE("millis + sleep") {
        const auto m1 = nada::time::millis();
        nada::time::sleep(100);
        const auto m2 = nada::time::millis();
        REQUIRE(m1 < m2);
        REQUIRE(m2 - m1 < 110); // 10% tolerance
    }

}};
