#pragma once

#include <doctest.h>

class Test_misc { TEST_CASE_CLASS("Test_misc") {

    SUBCASE("all_files") {
        // TODO
        auto all_files = nada::misc::all_files("/home/libnada/", "txt");
        for (auto f : all_files) std::cout << f << std::endl;
        REQUIRE(all_files.empty() == false);
    }

}};
