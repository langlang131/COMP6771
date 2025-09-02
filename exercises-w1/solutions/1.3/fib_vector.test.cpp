#include "fib_vector.h"

#include <catch2/catch.hpp>

TEST_CASE("Works when n == 0") {
    const auto expected = std::vector<int>{};
    auto nums = fibonacci(0);

    CHECK(nums == expected);
}

TEST_CASE("Works when n == 1") {
    auto nums = fibonacci(1);

    CHECK(!nums.empty());
    CHECK(nums.size() == 1);

    CHECK(nums[0] == 1);
    CHECK(nums.at(0) == 1);
}

TEST_CASE("Works when n is negative") {
    const auto expected = std::vector<int>{};

    auto nums = fibonacci(-1);

    CHECK(nums == expected);
}

TEST_CASE("Given example") {
    const auto expceted = std::vector<int>{1, 2, 3, 5, 8};

    auto nums = fibonacci(5);

    CHECK(nums == expceted);
}
