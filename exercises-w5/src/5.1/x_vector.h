#ifndef COMP6771_X_VECTOR
#define COMP6771_X_VECTOR

#include <initializer_list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class xector {
public:
    /**
        1. CONSTRUCTORS
    */

    // default constructor
    xector() = default;

    // construct from an initialiser list of std::strings
    xector(std::initializer_list<std::string>);

    xector(std::vector<std::string> const&);

    // copy constructor
    xector(xector const&);

    // destructor
    ~xector() = default;

    /**
        2. CLASS METHODS
     */

    // count the number of strings with an 'x'
    auto size() const -> size_t;

    // fetch the item at index i, or std::nullopt if none exists
    // this is esssentially the [] operator with a bounds check
    auto at(size_t const) const -> std::optional<std::string>;

    /**
        3. OPERATORS
     */

    // fetch item at ith spot
    // it is undefined behaviour to access a bad index
    auto operator[](size_t const) const -> std::string;
    
    // copy assignment operator
    auto operator=(xector const&) -> xector&;

    // check that all items considered by the left xector are the same as the one on the right
    friend auto operator==(xector const &a, xector const &b) -> bool;
private:
    std::vector<std::string> items_;
};

# endif // COMP6771_X_VECTOR