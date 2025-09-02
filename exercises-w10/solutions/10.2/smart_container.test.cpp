#include <catch2/catch.hpp>
#include "smart_container.h"

using namespace week10;

TEST_CASE("SmartContainer basic operations", "[smart_container]") {
    SmartContainer<int> container;

    SECTION("Empty container") {
        REQUIRE(container.empty());
        REQUIRE(container.size() == 0);
    }

    SECTION("Push back and access") {
        container.push_back(1);
        container.push_back(2);
        container.push_back(3);

        REQUIRE(container.size() == 3);
        REQUIRE(container[0] == 1);
        REQUIRE(container[1] == 2);
        REQUIRE(container[2] == 3);
    }

    SECTION("Emplace back") {
        container.emplace_back(1);
        container.emplace_back(2);

        REQUIRE(container.size() == 2);
        REQUIRE(container[0] == 1);
        REQUIRE(container[1] == 2);
    }

    SECTION("Range-based for loop") {
        container.push_back(1);
        container.push_back(2);
        container.push_back(3);

        int sum = 0;
        for (const auto& value : container) {
            sum += value;
        }
        REQUIRE(sum == 6);
    }

    SECTION("Exception safety") {
        REQUIRE_THROWS_AS(container.at(0), std::out_of_range);
        container.push_back(1);
        REQUIRE_NOTHROW(container.at(0));
        REQUIRE_THROWS_AS(container.at(1), std::out_of_range);
    }

    SECTION("Clear") {
        container.push_back(1);
        container.push_back(2);
        container.clear();
        REQUIRE(container.empty());
        REQUIRE(container.size() == 0);
    }
}

TEST_CASE("SmartContainer with custom type", "[smart_container]") {
    struct TestType {
        int value;
        TestType(int v) : value(v) {}
    };

    SmartContainer<TestType> container;

    SECTION("Push back custom type") {
        container.push_back(TestType(1));
        container.push_back(TestType(2));

        REQUIRE(container.size() == 2);
        REQUIRE(container[0].value == 1);
        REQUIRE(container[1].value == 2);
    }

    SECTION("Emplace back custom type") {
        container.emplace_back(1);
        container.emplace_back(2);

        REQUIRE(container.size() == 2);
        REQUIRE(container[0].value == 1);
        REQUIRE(container[1].value == 2);
    }
}

TEST_CASE("SmartContainer iterators", "[smart_container]") {
    SmartContainer<int> container;
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);

    SECTION("Iterator operations") {
        auto it = container.begin();
        REQUIRE(*it == 1);
        ++it;
        REQUIRE(*it == 2);
        it++;
        REQUIRE(*it == 3);
        ++it;
        REQUIRE(it == container.end());
    }

    SECTION("Const iterator") {
        const auto& const_container = container;
        auto it = const_container.begin();
        REQUIRE(*it == 1);
        ++it;
        REQUIRE(*it == 2);
    }

    SECTION("Iterator range") {
        int sum = 0;
        for (auto it = container.begin(); it != container.end(); ++it) {
            sum += *it;
        }
        REQUIRE(sum == 6);
    }
} 