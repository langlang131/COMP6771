#ifndef COMP6771_X_VECTOR
#define COMP6771_X_VECTOR

#include <initializer_list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

/**
    0. HELPER METHODS
 */

auto string_contains_special(std::string const s) -> bool;

class xector {
public:
    /**
        1. CONSTRUCTORS
    */

    // default constructor
    xector();
    // construct from an initialiser list
    xector(std::initializer_list<std::string>);
    // construct from a range in an existing std::vector
    xector(std::vector<std::string>::const_iterator, std::vector<std::string>::const_iterator);
    // construct from a std::vector
    xector(std::vector<std::string> const&);

    /**
        2. CLASS METHODS
     */

    // count the number of strings with an 'x'
    size_t size();

    // find the first string that contains an 'x'
    // return a std::nullopt_t if there are no such elements
    auto first() -> std::optional<std::string>;

    // find the last string that contains an 'x'
    // return a std::nullopt_t if there are no such elements
    auto last() const -> std::optional<std::string>;

    // add a new string to the end of the xector
    // note that this element may be ignored
    auto push_back(std::string) -> void;

private:
    std::vector<std::string> items_;
};

# endif // COMP6771_X_VECTOR