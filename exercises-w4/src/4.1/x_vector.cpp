#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "./x_vector.h"

#define SPECIAL_LETTER 'x'

/**
    0. HELPER METHODS
 */

auto string_contains_special(std::string const s) -> bool {
    // .find returns the constant npos if the character was not found
    return s.find(SPECIAL_LETTER) != std::string::npos;
}

/**
    1. CONSTRUCTORS
*/

xector::xector() {
    items_ = std::vector<std::string>();
}

xector::xector(std::initializer_list<std::string> items) {
    items_ = std::vector<std::string>();  
    for (auto i : items) {
        items_.push_back(i);
    }
}

xector::xector(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) : items_{start, end} {}

xector::xector(std::vector<std::string> const &items) {
    items_ = std::vector(items.begin(), items.end());
}

/**
    2. CLASS METHODS
*/

size_t xector::size() {
    size_t result = 0;
    for (size_t i = 0; i < items_.size(); ++i) {
        auto curr = items_.at(i);
        if (string_contains_special(curr)) {
            // add one to the result if we found a matching character
            ++result;
        }
    }
    return result;
}

auto xector::first() -> std::optional<std::string> {
    // TODO: test if this is needed
    // if (items_.empty()) {
    //     return std::nullopt;
    // }

    for (auto curr = items_.begin(); curr != items_.end(); ++curr) {
        if (string_contains_special(*curr)) {
            return std::optional<std::string>(*curr);
        }
    }

    return std::nullopt;
}

auto xector::last() const -> std::optional<std::string> {
    auto search = std::find_if(items_.rbegin(), items_.rend(), string_contains_special);
    return (search == items_.rend()) ? std::nullopt : std::optional<std::string>(*search);
}

auto xector::push_back(std::string item) -> void {
    items_.push_back(item);
}
