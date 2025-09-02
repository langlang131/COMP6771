#include "scale.h"

auto scale(std::vector<int> &ivec, double factor) -> std::vector<double> {
    auto dvec = std::vector<double>{};

    for (auto i : ivec) {
        auto new_double = static_cast<double>(i) * factor;
        dvec.push_back(new_double);
    }

    return dvec;
}
