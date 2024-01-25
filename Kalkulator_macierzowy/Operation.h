#pragma once
#include "Matrix.h"
#include <iostream>
#include <stack>
#include <regex>

class Operation
{
private:
	string infix;
	stack<char> stack;
	string postfix;

public:
	void load();
	int amountMatrix();
	void transpone(Matrix* table);
	void inverse(Matrix* table);
	void exponentation(Matrix* table);
	bool isOperator(char c);
	int getPrecedence(char op);
	void infixToPostfix();
	Matrix& calculate(Matrix* table);
	void clear();
};

