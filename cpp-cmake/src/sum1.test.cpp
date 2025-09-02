#include <catch2/catch.hpp>

#include "sum.h"

TEST_CASE("sum1") {
    CHECK(sum(1, 2) == 3);
}
