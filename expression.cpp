#include <iostream>

using namespace std;

struct Expression {
	virtual double evaluate() const = 0; // pure virtual

	virtual ~Expression() { }
};

struct Number : Expression {

	Number(double value) : value(value) { }

	double evaluate() const {
		return value;
	}

private:
	double value;
};

struct BinaryOperation : Expression {

	BinaryOperation(Expression const * left, char operation, Expression const * right) {
		this->left = left;
		this->right = right;
		this->operation = operation;
	}

	double evaluate() const {
		switch (operation) {
		case '+' :
			return left->evaluate() + right->evaluate();
		case '-':
			return left->evaluate() - right->evaluate();
		case '*':
			return left->evaluate() * right->evaluate();
		case '/':
			return left->evaluate() / right->evaluate();
		}
	}

	~BinaryOperation() {
		delete left;
		delete right;
	}

private:
	Expression const * left;
	Expression const * right;
	char operation;
};
