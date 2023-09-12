/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Number.cpp                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 13:01:13 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Number.h"


Number::Number() : Token(NumberType) {}

Number::Number(const Number &other)
: Token(NumberType), number_(other.number_) {}

Number::Number(int i)
: Token(NumberType), number_(i) {}

std::ostream &Number::operator<<(std::ostream &os) const {
	os << "Num(" << number_ << ")";
	return os;
}

Number &Number::operator=(const Number &other) {
	if (this == &other)
		return *this;
	number_ = other.number_;
	return *this;
}

Number::~Number() {
	Token::~Token();
}

bool Number::operator==(const Number &rhs) const {
	return number_ == rhs.number_;
}

bool Number::operator!=(const Number &rhs) const {
	return !(rhs == *this);
}

bool Number::operator<(const Number &rhs) const {
	return number_ < rhs.number_;
}

bool Number::operator>(const Number &rhs) const {
	return rhs < *this;
}

bool Number::operator<=(const Number &rhs) const {
	return !(rhs < *this);
}

bool Number::operator>=(const Number &rhs) const {
	return !(*this < rhs);
}

Number Number::operator+(const Number &rhs) const {
	return Number(number_ + rhs.number_);
}

Number Number::operator-(const Number &rhs) const {
	return Number(number_ - rhs.number_);
}

Number Number::operator*(const Number &rhs) const {
	return Number(number_ * rhs.number_);
}

Number Number::operator/(const Number &rhs) const {
	return Number(number_ / rhs.number_);
}

Token::Type Number::GetType() const {
	return NumberType;
}

int Number::GetNumber() const {
	return number_;
}
