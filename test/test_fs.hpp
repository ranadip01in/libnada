#pragma

#include <doctest.h>

class Test_misc { TEST_CASE_CLASS("Test_misc") {

    SUBCASE("all_files") {
        SUBCASE("txt") {
            const auto& all_files = nada::fs::all_files("test", "txt");
            REQUIRE_EQ(all_files.size(), 2);
        }
        SUBCASE("all files") {
            const auto& all_files = nada::fs::all_files("test", "");
            REQUIRE_EQ(all_files.size(), 4);
        }
        SUBCASE("cfg") {
            const auto& all_files = nada::fs::all_files("test", "cfg");
            REQUIRE_EQ(all_files.size(), 1);
            REQUIRE_EQ(all_files.at(0), "test/test_file_4.cfg");
        }
        SUBCASE("exe") {
            const auto& all_files = nada::fs::all_files("test", "exe");
            REQUIRE_EQ(all_files.size(), 0);
        }
    }

}};