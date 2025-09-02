#ifndef COMP6771_EXPR_H
#define COMP6771_EXPR_H

#include <memory>

class Expr {
public:
	virtual double eval() const = 0;
	virtual ~Expr() = default;
};

class Plus : public Expr {
public:
	Plus(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) noexcept
	: lhs_{std::move(l)}
	, rhs_{std::move(r)} {}

	double eval() const override {
		return lhs_->eval() + rhs_->eval();
	}

private:
	std::unique_ptr<Expr> lhs_;
	std::unique_ptr<Expr> rhs_;
};

class Minus : public Expr {
public:
	Minus(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) noexcept
	: lhs_{std::move(l)}
	, rhs_{std::move(r)} {}

	double eval() const override {
		return lhs_->eval() - rhs_->eval();
	}

private:
	std::unique_ptr<Expr> lhs_;
	std::unique_ptr<Expr> rhs_;
};

class Multiply : public Expr {
public:
	Multiply(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) noexcept
	: lhs_{std::move(l)}
	, rhs_{std::move(r)} {}

	double eval() const override {
		return lhs_->eval() * rhs_->eval();
	}

private:
	std::unique_ptr<Expr> lhs_;
	std::unique_ptr<Expr> rhs_;
};

class Divide : public Expr {
public:
	Divide(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) noexcept
	: lhs_{std::move(l)}
	, rhs_{std::move(r)} {}

	double eval() const override {
		return lhs_->eval() / rhs_->eval();
	}

private:
	std::unique_ptr<Expr> lhs_;
	std::unique_ptr<Expr> rhs_;
};

class Literal : public Expr {
public:
	Literal(double val) noexcept
	: val_{val} {}

	double eval() const override {
		return val_;
	}

private:
	double val_;
};

#endif // COMP6771_Expr_H
