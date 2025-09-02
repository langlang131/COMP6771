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
        * create an xector from an initialiser list of strings
     */
    xector(std::initializer_list<std::string>);

    /**
        * fetch the item at an index
        @throws a std::out_of_range if the index is out of bounds with message:
        * index <i> is out of range for an xector of size <n>
        * where <i> and <n> are replaced by the index and size of the xector respectively
     */
    auto at(size_t const) const -> std::string const&;

    /**
        @returns the number of strings with an 'x' in them
     */
    auto size() const -> size_t;
private:
    std::vector<std::string> items_;
};

# endif // COMP6771_X_VECTOR