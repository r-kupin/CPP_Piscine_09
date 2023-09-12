/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter.cpp                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/04 16:38:33 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Interpreter.h"
#include "tokens/Number.h"

Interpreter::Interpreter(const std::string &str)
: input_(str), numbers_(0), operators_(0), open_braces_(0), close_braces_(0) {
	if (input_.empty() ||
		input_.find_first_not_of("0123456789 ()-+*/") != kNotFound ||
		!InputIsCorrect())
		throw WrongInputException();
}

int Interpreter::GetNumbers() const {
	return numbers_;
}

int Interpreter::GetOperators() const {
	return operators_;
}

int Interpreter::GetOpenBraces() const {
	return open_braces_;
}

int Interpreter::GetCloseBraces() const {
	return close_braces_;
}

Interpreter::Interpreter() {}

std::ostream &operator<<(std::ostream &os, const Interpreter &interpreter) {
	for (MutantStack<Token *>::const_iterator it = interpreter.tokens_.begin();
			it != interpreter.tokens_.end() ; ++it) {
		(*it)->operator<<(os) << " ";
	}
	return os;
}

Interpreter::~Interpreter() {
	for (size_t i = 0; i < tokens_.size(); ++i) {
		delete tokens_[i];
	}
}

const std::deque<Token *> &Interpreter::GetTokens() const {
	return tokens_;
}

const char *Interpreter::WrongInputException::what() const throw() {
	return "Input expression is not correct";
}
