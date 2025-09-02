#include <algorithm>
#include <initializer_list>
#include <optional>
#include <string>
#include <vector>

#include "./x_vector.h"

/**
    0. HELPER METHODS
 */

namespace {
    auto const SPECIAL_PHRASE=  "piggy";
    auto string_contains_special(std::string const &s) -> bool;
}

/**
    1. CONSTRUCTORS
*/

xector::xector(std::initializer_list<std::string> items) : items_{items.begin(), items.end()} {}

xector::xector(std::vector<std::string> const& items) : items_{items.begin(), items.end()} {}

xector::xector(xector const& other) : items_{other.items_.begin(), other.items_.end()} {}

/**
    2. CLASS METHODS
*/

auto xector::size() const -> size_t {
    return static_cast<size_t>(std::count_if(items_.begin(), items_.end(), string_contains_special));
}

auto xector::at(size_t const i) const -> std::optional<std::string> {
    if (i >= this->size()) {
        return std::nullopt;
    }

    auto curr = items_.begin();
    auto seen = size_t{0};
    for (; curr != items_.end(); ++curr) {
        if (string_contains_special(*curr)) {
            if (seen == i) {
                break;
            }
            ++seen;
        }
    }
    return *curr;
}

/**
    3. OPERATORS
 */

auto xector::operator[](size_t const i) const -> std::string {
    auto curr = items_.begin();
    auto seen =  size_t{0};
    for (; curr != items_.end(); ++curr) {
        if (string_contains_special(*curr)) {
            if (seen == i) {
                break;
            }
            ++seen;
        }
    }
    return *curr;
}

auto xector::operator=(xector const &other) -> xector& {
    if (this != &other) {
        items_ = std::vector<std::string>{other.items_.begin(), other.items_.end()};
    }
    return *this;
}

auto operator==(xector const &a, xector const &b) -> bool {
    if (a.size() != b.size()) {
        return false;
    }
    for (auto i = size_t{0}; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

namespace {
    auto string_contains_special(std::string const &s) -> bool {
        // .find returns the constant npos if the character was not found
        return s.find(SPECIAL_PHRASE) != std::string::npos;
    }
}
