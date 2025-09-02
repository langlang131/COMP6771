#include "./x_vector.h"

#include <sstream>
#include <stdexcept>
#include <string>

namespace {
    auto const SPECIAL_LETTER=  'x';
    auto string_contains_special(std::string const &s) -> bool;
}

xector::xector(std::initializer_list<std::string> items) : items_{items.begin(), items.end()} {}

auto xector::size() const -> size_t {
    return static_cast<size_t>(std::count_if(items_.begin(), items_.end(), string_contains_special));
}

auto xector::at(size_t const i) const -> std::string const& {
    auto n = this->size();
    if (i >= n) {
        auto message = std::stringstream{};
        message << "index " << i << " is out of range for an xector of size " << n;
        throw std::out_of_range{message.str()};
    }

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

namespace {
    auto string_contains_special(std::string const &s) -> bool {
        // .find returns the constant npos if the character was not found
        return s.find(SPECIAL_LETTER) != std::string::npos;
    }
}
