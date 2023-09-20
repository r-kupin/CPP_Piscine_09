/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Operator.cpp                                       :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 17:21:39 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <iostream>
#include "Operator.h"

Operator::Operator() : Token(OperatorType){}

Operator::Operator(const Operator &other)
: Token(OperatorType), operator_(other.operator_), priority_(other.priority_) {}

/**
 * Constructor for Operator class that initializes the operator_ member variable
 * to the given character and sets the priority_ member variable based on the
 * operator's type. It also checks if the given operator is valid and throws an
 * exception if not.
 */
Operator::Operator(char an_operator)
: Token(OperatorType), operator_(an_operator) {
	if (std::string("+-*/").find(an_operator) == std::string::npos)
		throw WrongOperatorException();
	if (an_operator == '-' || an_operator == '+')
		priority_ = 1;
	if (an_operator == '/' || an_operator == '*')
		priority_ = 2;
}

Operator &Operator::operator=(const Operator &other) {
	if (this == &other)
		return *this;
	operator_ = other.operator_;
	priority_ = other.priority_;
	return *this;
}

Operator::~Operator() {
	Token::~Token();
}

std::ostream &Operator::operator<<(std::ostream &os) const {
	os << "Op(" << operator_ << ")";
	return os;
}

bool Operator::operator==(const Operator &rhs) const {
	return operator_ == rhs.operator_ && priority_ == rhs.priority_;
}

bool Operator::operator!=(const Operator &rhs) const {
	return !(rhs == *this);
}

bool Operator::operator<(const Operator &rhs) const {
	return priority_ < rhs.priority_;
}

bool Operator::operator>(const Operator &rhs) const {
	return rhs < *this;
}

bool Operator::operator<=(const Operator &rhs) const {
	return !(rhs < *this);
}

bool Operator::operator>=(const Operator &rhs) const {
	return !(*this < rhs);
}

Token::Type Operator::GetType() const {
	return OperatorType;
}

/**
 * Perform an arithmetic operation on two numbers.
 *
 * @param n1 The first number to perform the operation on.
 * @param n2 The second number to perform the operation on.
 *
 * @return A dynamically allocated Number object that holds the result of the
  operation.
 * The caller is responsible for deleting this object after use.
 */
Number Operator::perform(const Number &n1, const Number &n2) const {
	if (operator_ == '*') {
        if (PRINT)
		    std::cout << "Multiply ";
		return Number(n1 * n2);
	} else if (operator_ == '/') {
        if (PRINT)
		    std::cout << "Divide ";
		return Number(n1 / n2);
	} else if (operator_ == '+') {
        if (PRINT)
		    std::cout << "Add ";
		return Number(n1 + n2);
	} else if (operator_ == '-') {
        if (PRINT)
		    std::cout << "Substract  ";
		return Number(n1 - n2);
	} else
		return NULL;
}

char Operator::GetAnOperator() const {
	return operator_;
}

const char *Token::WrongOperatorException::what() const throw() {
	return "Character given as input should be an arithmetic operator +-/ or *";
}
