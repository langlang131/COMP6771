#include <utility>
#include <vector>

#include "mismatch.h"

auto mismatch(std::vector<int>& v1, std::vector<int>& v2) -> std::pair<iter, iter> {
    return std::make_pair(v1.begin(), v2.begin()); // dummy, remove
}
