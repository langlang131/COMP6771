#include <catch2/catch.hpp>

#include <stdexcept>

#include "./x_vector.h"

TEST_CASE("check that .at throws exception for bad index access") {
    auto states = xector{"california", "texas", "florida", "new mexico"};

    // only two items have an 'x' in them so there should be no index 2 (or 3rd item)
    try {
        states.at(2);
        REQUIRE(false);
    } catch (std::out_of_range const &_) {
        REQUIRE(true);
    }
}
