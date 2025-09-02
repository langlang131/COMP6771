#include "./filtered_string_view.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <set>
#include <sstream>

// TEST_CASE("filter me if you can") {
//     REQUIRE(false);
// }

// 2.4
TEST_CASE("default constructor") {
    auto sv = fsv::filtered_string_view{};
    REQUIRE(sv.size() == 0);
    REQUIRE(sv.empty());
    REQUIRE(sv.data() == nullptr);
}

TEST_CASE("string constructor") {
    auto s = std::string{"cat"};
    auto sv = fsv::filtered_string_view{s};
    REQUIRE(sv.size() == 3);
    REQUIRE(!sv.empty());
    REQUIRE(std::string{sv.data(), 3} == "cat");
}

TEST_CASE("string constructor with predicate - empty string") {
    auto s = std::string{""};
    auto pred = [](const char& c) { return c == 'z'; };
    auto sv = fsv::filtered_string_view{s, pred};
    REQUIRE(sv.size() == 0);
    REQUIRE(sv.empty());
}

TEST_CASE("string constructor with predicate") {
    auto s = std::string{"cat"};
    auto pred = [](const char& c) { return c == 'a'; };
    auto sv = fsv::filtered_string_view{s, pred};
    REQUIRE(sv.size() == 1);
}

TEST_CASE("implicit null-terminated string constructor") {
    auto sv = fsv::filtered_string_view{"cat"};
    REQUIRE(sv.size() == 3);
    REQUIRE(std::string{sv.data(), 3} == "cat");
}

TEST_CASE("null-terminated string with predicate") {
    auto pred = [](const char& c) { return c == 'a'; };
    auto sv = fsv::filtered_string_view{"cat", pred};
    REQUIRE(sv.size() == 1);
}

TEST_CASE("copy constructor sv1 equal sv2") {
    auto sv1 = fsv::filtered_string_view{"cat"};
    auto sv2 = fsv::filtered_string_view{sv1};
    REQUIRE(sv1.data() == sv2.data());
    REQUIRE(sv2.size() == sv1.size());
    REQUIRE_FALSE(sv2.empty());
}

TEST_CASE("move constructor transfers view and resets the original object to empty") {
    auto sv1 = fsv::filtered_string_view{"cat"};
    const auto original_ptr = sv1.data();
    auto sv2 = fsv::filtered_string_view{std::move(sv1)};
    REQUIRE(sv2.data() == original_ptr);
    REQUIRE(sv2.size() == 3);
    REQUIRE(sv1.data() == nullptr);
    REQUIRE(sv1.empty());
}

TEST_CASE("copy with predicate preserves filter") {
    auto pred = [](const char& c) { return c != 'l'; };
    auto sv1 = fsv::filtered_string_view{"hello", pred};
    auto sv2 = fsv::filtered_string_view{sv1};
    REQUIRE(sv2.size() == 3); // h, e, o
}

// 2.5
TEST_CASE("copy assignment self-copy") {
    auto pred = [](const char& c) { return c == '4' || c == '2'; };
    auto fsv1 = fsv::filtered_string_view{"42 bro", pred};
    auto fsv2 = fsv::filtered_string_view{};
    fsv2 = fsv1;
    REQUIRE(fsv1.data() == fsv2.data());
    REQUIRE(fsv1.size() == fsv2.size());
    for (std::size_t i = 0; i < fsv1.size(); ++i) {
        REQUIRE(fsv1[i] == fsv2[i]);
    }
}

TEST_CASE("move assignment should remain unchanged") {
    auto pred = [](const char& c) { return c == '8' || c == '9'; };
    auto fsv1 = fsv::filtered_string_view{"'89 baby", pred};
    const auto original_ptr = fsv1.data();
    auto fsv2 = fsv::filtered_string_view{};
    fsv2 = std::move(fsv1);
    REQUIRE(fsv2.data() == original_ptr);
    REQUIRE(fsv1.data() == nullptr);
    REQUIRE(fsv1.size() == 0);
}

TEST_CASE("use subscript access character") {
    auto pred = [](const char& c) { return c == '9' || c == '0' || c == ' '; };
    auto fsv1 = fsv::filtered_string_view{"only 90s kids understand", pred};
    REQUIRE(fsv1.size() >= 3);
    REQUIRE(fsv1[0] == ' ');
    REQUIRE(fsv1[1] == '9');
    REQUIRE(fsv1[2] == '0');
}

// 2.5.4
TEST_CASE("explicit conversion to std::string") {
    auto sv = fsv::filtered_string_view("vizsla");
    auto s = static_cast<std::string>(sv);
    REQUIRE(s == "vizsla");
    REQUIRE(s.data() != sv.data());
}

TEST_CASE("conversion include punctuation and whitespace") {
    auto sv = fsv::filtered_string_view("how are you, mate!");
    auto s = static_cast<std::string>(sv);
    REQUIRE(s == "how are you, mate!");
}

TEST_CASE("conversion with predicate") {
    auto pred = [](const char& c) { return c == 'z' || c == 'l'; };
    auto sv = fsv::filtered_string_view("vizsla", pred);
    auto s = static_cast<std::string>(sv);
    REQUIRE(s == "zl");
}

// 2.6.1
TEST_CASE("at() with valid index") {
    auto vowels = std::set<char>{'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
    auto is_vowel = [&vowels](const char& c) { return vowels.find(c) != vowels.end(); };
    auto sv = fsv::filtered_string_view("Malamute", is_vowel);
    REQUIRE(sv.at(0) == 'a');
    REQUIRE(sv.at(1) == 'a');
    REQUIRE(sv.at(2) == 'u');
    REQUIRE(sv.at(3) == 'e');
}

TEST_CASE("at() with invalid index") {
    auto sv = fsv::filtered_string_view("");
    REQUIRE_THROWS_AS(sv.at(0), std::domain_error);
    REQUIRE_THROWS_WITH(sv.at(0), "filtered_string_view::at(0): invalid index");
}

// 2.6.2
TEST_CASE("size() on string") {
    auto sv = fsv::filtered_string_view("Maltese");
    REQUIRE(sv.size() == 7);
}

TEST_CASE("size() on filtered string") {
    auto sv = fsv::filtered_string_view("Toy Poodle", [](const char& c) { return c == 'o'; });
    REQUIRE(sv.size() == 3);
}

// 2.6.3
TEST_CASE("empty() on non-empty string") {
    auto sv = fsv::filtered_string_view("Australian Shephard");
    REQUIRE_FALSE(sv.empty());

    auto empty_sv = fsv::filtered_string_view{};
    REQUIRE(empty_sv.empty());
}

TEST_CASE("empty() with filter no 'z' in 'Border Collie'") {
    auto sv = fsv::filtered_string_view("Border Collie", [](const char& c) { return c == 'z'; });
    REQUIRE(sv.empty());
}

// 2.6.4
TEST_CASE("data() return original pointer") {
    const char* s = "Sum 42";
    auto sv = fsv::filtered_string_view{s, [](const char& c) {
                                            (void)c;
                                            return false;
                                        }};
    std::string reconstructed;
    for (auto ptr = sv.data(); *ptr; ++ptr) {
        reconstructed += *ptr;
    }
    REQUIRE(reconstructed == "Sum 42");
}

// 2.6.5
TEST_CASE("check predicate() returns the filtering function") {
    const auto print_and_return_true = [](const char&) {
        std::cout << "hi!";
        return true;
    };
    auto sv = fsv::filtered_string_view("doggo", print_and_return_true);
    std::stringstream buffer;
    std::streambuf* old_buf = std::cout.rdbuf(buffer.rdbuf());

    const auto& predicate = sv.predicate();
    predicate('x'); // "hi!"

    std::cout.rdbuf(old_buf);
    REQUIRE(buffer.str() == "hi!");
}

// 2.7.1
TEST_CASE("Equality Comparison") {
    auto const lo = fsv::filtered_string_view{"aaa"};
    auto const hi = fsv::filtered_string_view{"zzz"};

    REQUIRE_FALSE(lo == hi);
    REQUIRE(lo != hi);
}

TEST_CASE("Equality Comparison - equal after filtering") {
    auto is_not_a = [](const char& c) { return c != 'a'; };
    fsv::filtered_string_view s1{"banana", is_not_a};
    fsv::filtered_string_view s2{"bnn"};

    REQUIRE(s1 == s2);
    REQUIRE_FALSE(s1 != s2);
}

// 2.7.2 (manually implemented)
TEST_CASE("relational comparison") {
    auto a = fsv::filtered_string_view("apple");
    auto b = fsv::filtered_string_view("banana");
    REQUIRE(a < b);
    REQUIRE(b > a);
    REQUIRE(a <= b);
    REQUIRE(b >= a);
    REQUIRE(a <= a);
    REQUIRE(a >= a);

    SECTION("comparison with filters 1") {
        auto sv1 = fsv::filtered_string_view("banana", [](const char& c) { return c != 'n'; }); // baaa
        auto sv2 = fsv::filtered_string_view("banana", [](const char& c) { return c != 'b'; }); // anana
        REQUIRE(sv1 > sv2); // baaa > anana
    }
    SECTION("comparison with filters 2") {
        auto lo = fsv::filtered_string_view{"horn"};
        auto hi = fsv::filtered_string_view{"a mule", [](const char& c) { return c != 'a' && c != ' '; }};
        REQUIRE(lo < hi); // horn < mule
    }
}
// 2.7.3
TEST_CASE("output stream operator<<") {
    SECTION("without filter") {
        std::ostringstream oss;
        auto f = fsv::filtered_string_view{"hello"};
        oss << f;
        REQUIRE(oss.str() == "hello");
    }

    SECTION("with filter c++") {
        std::ostringstream oss;
        auto f = fsv::filtered_string_view{"c++ > rust > java", [](const char& c) { return c == 'c' || c == '+'; }};
        oss << f;
        REQUIRE(oss.str() == "c++");
    }
}
// 2.8.1
TEST_CASE("compose ") {
    SECTION("compose multiple filters") {
        auto base = fsv::filtered_string_view{"c / c++"};
        auto vf = std::vector<fsv::filter>{[](const char& c) { return c == 'c' || c == '+' || c == '/'; },
                                           [](const char& c) { return c > ' '; },
                                           [](const char& c) {
                                               (void)c;
                                               return true;
                                           }};
        auto composed = fsv::compose(base, vf);
        REQUIRE(static_cast<std::string>(composed) == "c/c++");
    }
    SECTION("all filter true") {
        auto sv = fsv::filtered_string_view{"hello123"};
        auto vf = std::vector<fsv::filter>{[](const char& c) {
                                               (void)c;
                                               return true;
                                           },
                                           [](const char& c) {
                                               (void)c;
                                               return true;
                                           },
                                           [](const char& c) {
                                               (void)c;
                                               return true;
                                           }};
        auto result = fsv::compose(sv, vf);
        REQUIRE(static_cast<std::string>(result) == "hello123");
    }
}
// 2.8.2
TEST_CASE("split") {
    SECTION("split sample") {
        auto wentworth = fsv::filtered_string_view{"Malcom? Bligh? Turnbull", [](const char& c) { return c != '?'; }};
        auto token = fsv::filtered_string_view{" 2015", [](const char& c) { return c == ' '; }};
        auto representative = fsv::split(wentworth, token);
        REQUIRE(representative.size() == 3);
        REQUIRE(static_cast<std::string>(representative.at(1)) == "Bligh");
    }

    SECTION("tok does not appear in fsv") {
        auto fsv1 = fsv::filtered_string_view{"fishing"};
        auto empty_tok = fsv::filtered_string_view{""};
        auto empty_split = fsv::split(fsv1, empty_tok);

        auto fill_tok = fsv::filtered_string_view{"robert"};
        auto fill_split = fsv::split(fsv1, fill_tok);

        REQUIRE(empty_split.size() == 1);
        REQUIRE(fill_split.size() == 1);
        REQUIRE(empty_split == fill_split);
        REQUIRE(static_cast<std::string>(empty_split.at(0)) == "fishing");
    }

    SECTION("xax split by x") {
        auto sv = fsv::filtered_string_view{"xax"};
        auto tok = fsv::filtered_string_view{"x"};
        auto v = fsv::split(sv, tok);
        REQUIRE(v.size() == 3);
        REQUIRE(static_cast<std::string>(v[0]) == "");
        REQUIRE(static_cast<std::string>(v[1]) == "a");
        REQUIRE(static_cast<std::string>(v[2]) == "");
    }

    SECTION("xx split by x") {
        auto sv = fsv::filtered_string_view{"xx"};
        auto tok = fsv::filtered_string_view{"x"};
        auto v = fsv::split(sv, tok);
        REQUIRE(v.size() == 3);
        REQUIRE(static_cast<std::string>(v[0]) == "");
        REQUIRE(static_cast<std::string>(v[1]) == "");
        REQUIRE(static_cast<std::string>(v[2]) == "");
    }
}
// 2.8.3
TEST_CASE("substr") {
    SECTION("basic test no filter") {
        auto sv = fsv::filtered_string_view{"new york city"};
        REQUIRE(static_cast<std::string>(fsv::substr(sv, 4, 4)) == "york");

        auto sv2 = fsv::filtered_string_view{"black pen"};
        REQUIRE(static_cast<std::string>(fsv::substr(sv2, 6)) == "pen");
    }

    SECTION("filter uppercase only, throw when pos exceeds size") {
        auto fsv1 = fsv::filtered_string_view{"the right honourable. anthony charles lynton BLAIR",
                                              [](const char& c) { return c >= 'A' && c <= 'Z'; }};
        REQUIRE(fsv1.size() == 5);
        REQUIRE_THROWS_WITH(fsv::substr(fsv1, 6),
                            "filtered_string_view::substr(6): position out of range for filtered string of size 5");
    }

    SECTION("empty substrings") {
        auto fsv1 = fsv::filtered_string_view{"notebook"};
        auto sub1 = fsv::substr(fsv1, 8);
        auto sub2 = fsv::substr(fsv1, 3, 0);
        REQUIRE(sub1.empty());
        REQUIRE(sub2.empty());
    }
}