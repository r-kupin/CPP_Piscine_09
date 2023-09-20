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

Interpreter:: Interpreter(const std::string &str)
: input_(str), numbers_(0), operators_(0), open_braces_(0), close_braces_(0) {
	if (input_.empty() ||
		input_.find_first_not_of("0123456789 -+*/") != kNotFound ||
		!InputIsCorrect())
		throw WrongInputException();
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
    for (std::deque<Token *>::iterator dequeIterator = tokens_.begin();
         dequeIterator != tokens_.end(); ++dequeIterator) {
        delete *dequeIterator;
    }
}

const char *Interpreter::WrongInputException::what() const throw() {
	return "Input rpn expression is not correct";
}
