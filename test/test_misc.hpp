#pragma once

#include <doctest.h>
#include <nada/misc.hpp>
#include <functional>

class Test_misc { TEST_CASE_CLASS("Test_misc") {

    SUBCASE("do_once") {
        unsigned count = 0;
        for (unsigned i = 0; i < 10; i++) {
            NADA_DO_ONCE { count++; }
        }
        REQUIRE(count == 1);
    }

    SUBCASE("nada_sum") {
        std::vector<unsigned> v = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        const auto sum = NADA_SUM(v, std::plus());
        REQUIRE(sum == 10);
    }

}};
