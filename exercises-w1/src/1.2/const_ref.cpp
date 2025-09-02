#include <iostream>

static auto fn_1() -> void;
static auto fn_2() -> void;
static auto fn_3() -> void;
static auto fn_4() -> void;

int main(void) {
    fn_1();
    fn_2();
    fn_3();
    fn_4();

    return 0;
}


// Auto
static auto fn_1() -> void {
    auto i = 3;
    i = 4;
    std::cout << i << "\n";
}


// Auto and Const
static auto fn_2() -> void {
    auto const j = 5;
    --j;
    std::cout << j << "\n";
}


// Reference
static auto fn_3() -> void {
    auto age = 18;
    auto& my_age = age;
    ++my_age;
    std::cout << my_age << "\n";
}


// Const and Reference
static auto fn_4() -> void {
    auto age = 21;
    const auto &my_age = age;
    --my_age;
    std::cout << my_age << "\n";
}
