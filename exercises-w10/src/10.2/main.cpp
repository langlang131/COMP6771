#include "smart_container.h"
#include <iostream>
#include <string>

using week10::SmartContainer;

int main() {
    // Default construction
    SmartContainer<int> a;
    std::cout << "a.size(): " << a.size() << "\n";

    // Initializer list construction
    SmartContainer<int> b{1, 2, 3};
    std::cout << "b: ";
    for (const auto& x : b) std::cout << x << ' ';
    std::cout << "\n";

    // push_back and emplace_back
    b.push_back(4);
    b.emplace_back(5);
    std::cout << "b after push_back/emplace_back: ";
    for (const auto& x : b) std::cout << x << ' ';
    std::cout << "\n";

    // Copy and move
    SmartContainer<int> c = b;
    std::cout << "c (copy of b): ";
    for (const auto& x : c) std::cout << x << ' ';
    std::cout << "\n";

    SmartContainer<int> d = std::move(c);
    std::cout << "d (moved from c): ";
    for (const auto& x : d) std::cout << x << ' ';
    std::cout << "\n";
    std::cout << "c.size() after move: " << c.size() << "\n";

    // Element access
    std::cout << "d[2]: " << d[2] << "\n";
    d[2] = 42;
    std::cout << "d after d[2]=42: ";
    for (const auto& x : d) std::cout << x << ' ';
    std::cout << "\n";

    // Exception safety
    try {
        std::cout << d.at(100) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    // Equality
    SmartContainer<int> e{1, 2, 42, 4, 5};
    std::cout << "d == e: " << (d == e ? "true" : "false") << "\n";

    // Custom type
    struct Person {
        std::string name;
        int age;
        bool operator==(const Person& rhs) const { return name == rhs.name && age == rhs.age; }
    };
    SmartContainer<Person> people;
    people.emplace_back(Person{"Alice", 30});
    people.push_back({"Bob", 25});
    for (const auto& p : people) {
        std::cout << p.name << ": " << p.age << "\n";
    }
} 