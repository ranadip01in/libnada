#pragma once

#include <doctest.h>
#include <nada/ini.hpp>

class Test_ini { TEST_CASE_CLASS("Test_ini") {

    SUBCASE("file good") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.good() == true);
    }

    SUBCASE("file bad") {
        nada::Ini ini("non_existing_file.ini");
        REQUIRE(ini.good() == false);
    }

    SUBCASE("value_str") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get("value_str") == "test");
    }

    SUBCASE("value_float") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get_float<double>("value_float") == doctest::Approx(-1.0));
    }

    SUBCASE("value_int") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get_int<int>("value_int") == -1);
    }

}};
