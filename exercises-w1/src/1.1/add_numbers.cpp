#include <iostream>

int main(void) {
	auto a = 0;
	auto b = 0;

	std::cout << "Please enter two numbers:";

	if (!(std::cin >> a) || !(std::cin >> b)) {
		std::cerr << "Something went wrong while reading an integer, bailing...\n";
		return -1;
	}
	auto sum = a + b;
	std::cout << sum << "\n";
	return 0;
};
