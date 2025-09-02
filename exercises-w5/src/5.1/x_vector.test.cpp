#include "./x_vector.h"

#include <iostream>
#include <optional>
#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("individual .at") {
    auto advice = xector{
        "good morning",
        "do you piggyback in C++?",
        "no i don't",
        "that's a shame, I always piggyback in C++!"
    };
    CHECK(advice.at(1).has_value());
    CHECK(*advice.at(1) == std::string{"that's a shame, I always piggyback in C++!"});
}

TEST_CASE("check xectors are equal") {
    auto north = xector{
        "ned",
        "piggy snack!",
        "stark",
        "peppa the piggy"
    };
    auto crown = xector{
        "robert",
        "piggy snack!",
        "baratheon",
        "peppa the piggy"
    };

    // now check for equality

    // size equality
    CHECK(north.size() == 2);
    CHECK(north.size() == crown.size());

    // index 0
    CHECK(north.at(0).has_value());
    CHECK(*north.at(0) == std::string{"piggy snack!"});

    CHECK(crown.at(0).has_value());
    CHECK(*crown.at(0) == std::string{"piggy snack!"});

    // index 1
    CHECK(north.at(1).has_value());
    CHECK(*north.at(1) == std::string{"peppa the piggy"});

    CHECK(crown.at(1).has_value());
    CHECK(*crown.at(1) == std::string{"peppa the piggy"});
}
