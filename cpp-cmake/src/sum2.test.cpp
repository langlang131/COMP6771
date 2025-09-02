#include <catch2/catch.hpp>

#include "sum.h"

TEST_CASE("sum2") {
    CHECK(sum(3, 4) != 6);
}
