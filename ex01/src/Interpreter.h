/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter.h                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/04 16:38:33 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX01_INTERPRETER_H
#define EX01_INTERPRETER_H

#include <string>
#include <ostream>
#include <stack>
#include "tokens/Token.h"
#include "MutantStack.h"
#include "tokens/Number.h"
#include "tokens/Operator.h"

#ifndef PRINT
# define PRINT false
#endif

const static unsigned long kNotFound = std::string::npos;

struct Interpreter {
	class WrongInputException : public std::exception {
	public:
		const char *what() const throw();
	};

	Interpreter();
	explicit Interpreter(const std::string &str);

	virtual ~Interpreter();

	void make_tokens();
	int evaluate();
	friend std::ostream &
	operator<<(std::ostream &os, const Interpreter &interpreter);

protected:
	int GetOperators() const;
	int GetOpenBraces() const;
	int GetCloseBraces() const;
	int GetNumbers() const;

private:
	bool InputIsCorrect();

	std::string input_;
	int numbers_;
	int operators_;
	int open_braces_;
	int close_braces_;
	std::deque<Token *> tokens_;
};

#endif //EX01_INTERPRETER_H
