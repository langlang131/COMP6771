#include "./x_vector.h"

#include <catch2/catch.hpp>

#include <random>

TEST_CASE("complex example") {
    // there is an x somewhere in this string
    auto xec = xector{"aaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffkkkkkkldsjkfewjrbhjjregbreoijreioxkljdfjkhkjbbbbbboioioerjhgioeriouioqw"};

    CHECK(xec.size() == 1);
}

TEST_CASE("simple xector without good element") {
    auto xec = xector{"robert", "ned", "hoster", "jon"};

    CHECK(xec.size() == 0);
}

TEST_CASE("simple xector with good elements") {
    auto xec = xector{"shanghai", "xian", "beijing", "shenzen", "wuxi"};

    CHECK(xec.size() == 2);
}

// pick a random number from [0, high);
auto pick_random_number(size_t high) -> size_t {
    // this code is taken from: https://en.cppreference.com/w/cpp/numeric/random/normal_distribution.html

    auto rd = std::random_device{};
    auto gen = std::mt19937{rd()};
    auto d = std::normal_distribution{5.0, 2.0};

    // Draw a sample from the normal distribution and round it to an integer.
    auto random_int = [&d, &gen]{ return std::lround(d(gen)); };

    return static_cast<size_t>(random_int()) % high;
}

TEST_CASE("comprehensive runtime-verified test") {
    // all of these items should be considered by the xector
    auto good = std::vector<std::string>{"xray", "extreme", "duplex", "blaxland"};

    // pick a random index to check - any of them should work
    auto choice = pick_random_number(good.size());
    auto xec= xector{good.at(choice)};
    CHECK(xec.size() == 1);
}

TEST_CASE("checking many individual correct strings") {
    auto good = std::vector<std::string>{"xray", "extreme", "duplex", "blaxland"};

    auto xec = xector();
    for (auto const& g : good) {
        xec.push_back(g);
        CHECK(xec.last() == g);
    }
}

TEST_CASE("vector simple constructor test") {
    auto xec = xector();
    CHECK(xec.size() == 0);
}

TEST_CASE("") {
    auto items = std::vector<std::string>{"xdisregard", "climb", "axel", "apex", "xdisregard"};
    auto start = items.begin();
    // put start at index 2
    ++start;
    ++start;
    auto end = items.end();
    // put end at index 4
    --end;
    // create xector in range [1, 4)
    auto xec_range = xector(start, end);

    CHECK(xec_range.first() == std::string{"axel"});
    CHECK(xec_range.last() == std::string{"apex"});

    // now test the full vector
    auto xec_default = xector(items);
    CHECK(xec_default.size() == 4);
}

TEST_CASE("checking helper function string contains") {
    CHECK(string_contains_special("xray"));
    
    CHECK(not string_contains_special("jaime"));
}
