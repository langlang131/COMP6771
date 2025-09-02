#include "./expr.h"

#include <iostream>

int main() {
	std::unique_ptr<Expr> expr = std::make_unique<Plus>(
	   std::make_unique<Multiply>(
	      std::make_unique<Divide>(std::make_unique<Literal>(2000), std::make_unique<Literal>(4)),
	      std::make_unique<Literal>(13)),
	   std::make_unique<Minus>(
	      std::make_unique<Literal>(700),
	      std::make_unique<Plus>(
	         std::make_unique<Multiply>(std::make_unique<Literal>(60), std::make_unique<Literal>(7)),
	         std::make_unique<Literal>(9))));

	std::cout << "COMP" << static_cast<int>(expr->eval()) << ": Advanced C++ Programming\n";
}
/**
 * Output:
 * COMP6771: Advanced C++ Programming
 */
