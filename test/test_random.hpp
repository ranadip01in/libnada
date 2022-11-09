#pragma once

#include <doctest.h>
#include <nada/random.hpp>

class Test_ramdom { TEST_CASE_CLASS("Test_random") {

    SUBCASE("100%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(100));
        REQUIRE(std::find(bools.begin(), bools.end(), false) == bools.end());
    }

    SUBCASE("50%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(50));
        REQUIRE(std::find(bools.begin(), bools.end(), false) != bools.end());
        REQUIRE(std::find(bools.begin(), bools.end(), true) != bools.end());
    }

    SUBCASE("0%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(0));
        REQUIRE(std::find(bools.begin(), bools.end(), true) == bools.end());
    }

}};
