#ifndef COMP6771_EXPR_H
#define COMP6771_EXPR_H

#include <memory>
class Expr {
public:
	virtual double eval() const = 0;
	virtual ~Expr() = default;
};

#endif // COMP6771_EXPR_H
