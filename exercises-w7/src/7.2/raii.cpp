#include <iostream>
#include <memory>

struct data {
    data(int n) : number_{std::make_unique<int>(n)} {}

    ~data(void) = default;

    std::unique_ptr<int> number_;
};

auto demo(void) -> void {
    auto territories = data(2);
    std::cout << "there are " << territories.number_.operator*() << " territories in the Commonwealth of Australia\n";
}

auto main(void) -> int {
    demo();
    return 0;
}
