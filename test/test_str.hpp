#pragma once

#include <doctest.h>
#include <nada/str.hpp>

class Test_str { TEST_CASE_CLASS("Test_str") {

    SUBCASE("nada::str::tokenize") {
        std::string s1("1;2;3;4");
        SUBCASE("example use") {
            const auto& tokens = nada::str::tokenize(s1, ';');
            REQUIRE(tokens.size() == 4);
            REQUIRE(tokens.at(0) == "1");
            REQUIRE(tokens.at(1) == "2");
            REQUIRE(tokens.at(2) == "3");
            REQUIRE(tokens.at(3) == "4");
        }
        SUBCASE("token not found") {
            const auto& tokens = nada::str::tokenize(s1, '+');
            REQUIRE(tokens.size() == 1);
            REQUIRE(tokens.at(0) == s1);
        }
    }

    SUBCASE("nada::str::replace with str") {
        std::string s1("nobody expects the spanish inquisition");
        nada::str::replace(s1, " ", "---");
        REQUIRE(s1 == "nobody---expects---the---spanish---inquisition");
    }

    SUBCASE("nada::str::replace with char") {
        std::string s1("nobody expects the spanish inquisition");
        nada::str::replace(s1, ' ', '-');
        REQUIRE(s1 == "nobody-expects-the-spanish-inquisition");
    }

    SUBCASE("nada::str::replace with max") {
        std::string s1("nobody expects the spanish inquisition");
        nada::str::replace(s1, " ", "-", 3);
        REQUIRE(s1 == "nobody-expects-the-spanish inquisition");
    }

    SUBCASE("nada::str::get_between") {
        const std::string s1("nobody expects <the spanish> inquisition");
        SUBCASE("example use") {
            const auto& the_spanish = nada::str::get_between(s1, '<', '>');
            REQUIRE(the_spanish == "the spanish");
        }
        SUBCASE("invalid case") {
            const auto& nothing_here = nada::str::get_between(s1, '+', '+');
            REQUIRE(nothing_here == "");
        }
        SUBCASE("something you might or might not expect") {
            const auto& maybe_expected = nada::str::get_between(s1, ' ', ' ');
            REQUIRE(maybe_expected == "expects");
        }
        SUBCASE("better example for equals left and right token") {
            const std::string s2("this is a *better* example!");
            const auto& definitely_expected = nada::str::get_between(s2, '*', '*');
            REQUIRE(definitely_expected == "better");
        }
    }

    SUBCASE("nada::str::to_lower") {
        std::string s1("NoBoDy ExPeCtS <ThE SpAnIsH> InqUISItioN!!!11");
        nada::str::to_lower(s1);
        REQUIRE(s1 == "nobody expects <the spanish> inquisition!!!11");
    }

    SUBCASE("nada::str::find") {
        const std::string s1("nobody expects the spanish inquisition");
        SUBCASE("find the first o") {
            const auto find = nada::str::find(s1, "o", 0);
            REQUIRE(find == 1); // finds nObody
        }
        SUBCASE("find the second o") {
            const auto find = nada::str::find(s1, "o", 1);
            REQUIRE(find == 3); // finds nobOdy
        }
        SUBCASE("find the first o after position 10") {
            const auto find = nada::str::find(s1, "o", 0, 10);
            REQUIRE(find == 36); // finds the o in inquisition
        }
    }

    SUBCASE("nada::str::find_after") {
        const std::string s1("nobody expects the spanish inquisition");
        SUBCASE("find the first o") {
            const auto find = nada::str::find_after(s1, "o", "n");
            REQUIRE(find == 1); // finds nObody (because it's the first 'o' after the first 'n')
        }
        SUBCASE("find the first o") {
            const auto find = nada::str::find_after(s1, "o", "spanish");
            REQUIRE(find == 36); // finds the o in inquisition (because it's after 'spanish')
        }
    }

    SUBCASE("nada::str::remove") {
        std::string s1("nobody expects the spanish inquisition");
        const std::string original = s1; // copy for comparasion
        SUBCASE("remove something that's not there does nothing") {
            nada::str::remove(s1, '+');
            REQUIRE(s1 == original);
        }
        SUBCASE("remove the spanish") {
            nada::str::remove(s1, ' ');
            REQUIRE(s1 == "nobodyexpectsthespanishinquisition");
        }
    }

    SUBCASE("remove_whitespace") {
        std::string s1("nobody expects the spanish inquisition");
        nada::str::remove_whitespace(s1);
        REQUIRE(s1 == "nobodyexpectsthespanishinquisition");
    }

}};
