/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Parenthesis.cpp                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 18:21:44 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Parenthesis.h"


Parenthesis::Parenthesis() {}

Parenthesis::Parenthesis(const Parenthesis &other) {
	type_ = other.type_;
}

Parenthesis::Parenthesis(Token::Type type) : Token(type) {}

Parenthesis &Parenthesis::operator=(const Parenthesis &other) {
	if (this == &other)
		return *this;
	type_ = other.type_;
	return *this;
}

std::ostream &Parenthesis::operator<<(std::ostream &os) const {
	if (type_ == ParenthesisOpen) {
		os << "ParOpen";
	} else if (type_ == ParenthesisClose) {
		os << "ParClose";
	}
	return os;
}

Token::Type Parenthesis::GetType() const {
	return type_;
}

Parenthesis::~Parenthesis() {
	Token::~Token();
}

bool Parenthesis::operator==(const Parenthesis &rhs) const {
	return type_ == rhs.type_;
}
