#ifndef COMP6771_PERMUTATION_H
#define COMP6771_PERMUTATION_H

#include <string>

/**
 * Determines if the string `x` is a permutation of the string `y`.
 * It is possible for one or either of these strings to be the empty string.
 */
auto is_permutation(const std::string &x, const std::string &y) -> bool;

#endif // COMP6771_PERMUTATION_H
