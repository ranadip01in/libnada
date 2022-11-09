#pragma once

#include <doctest.h>
#include <nada/log.hpp>

class Test_log { TEST_CASE_CLASS("Test_log") {

    SUBCASE("Log set output") {
        using namespace nada;
        std::ostringstream os;
        Log::set_output(&os);
        REQUIRE(os.str().empty() == true);
        Log::out() << "test";
        REQUIRE(os.str() == "test");
        Log::to_cout();
        Log::out() << "test";
        Log::out() << Log::flush;
        Log::out() << Log::endl;
        REQUIRE(os.str() == "test");
    }

    SUBCASE("Log::out()") {
        using namespace nada;
        std::ostringstream os;
        Log::set_output(&os);
        REQUIRE(os.str().empty() == true);
        Log::out() << "test";
        REQUIRE(os.str() == "test");
        Log::to_cout();
    }

    SUBCASE("Log::err()") {
        using namespace nada;
        std::ostringstream os;
        Log::set_output(&os);
        REQUIRE(os.str().empty() == true);
        Log::err() << "test";
        REQUIRE(os.str() == "test");
        Log::to_cout();
    }

    SUBCASE("Log::debug()") {
        using namespace nada;
        std::ostringstream os;
        Log::set_output(&os);
        REQUIRE(os.str().empty() == true);
        Log::debug() << "test";
        #ifdef NDEBUG
        REQUIRE(os.str().empty());
        #else
        REQUIRE(os.str() == "test");
        #endif
        Log::to_cout();
    }

    SUBCASE("Log::benchmark()") {
        using namespace nada;
        int i = 0;
        auto set_i_to_1 = [&]() { i = 1; };
        Log::benchmark(set_i_to_1, "benchmark function run");
        REQUIRE(i == 1);
    }

    SUBCASE("Log::benchmark()") {
        using namespace nada;
        int i = 0;
        auto set_i_to_1 = [&]() { i = 1; };
        Log::benchmark_debug(set_i_to_1, "debug benchmark function run");
        #ifdef NDEBUG
        REQUIRE(i == 0);
        #else
        REQUIRE(i == 1);
        #endif
    }

}};
