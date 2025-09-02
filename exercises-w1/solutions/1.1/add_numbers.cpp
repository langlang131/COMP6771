#include <iostream>

int main(void) {
    auto i = 0;
    auto j = 0;

    std::cout << "Please enter two numbers: ";

    if (!(std::cin >> i) || !(std::cin >> j)) {
        std::cerr << "Something went wrong while reading an integer, bailing...\n";
        return -1;
    }
    const auto sum = i + j;
    std::cout << "Sum: " << sum << "\n";
    return 0;
}
