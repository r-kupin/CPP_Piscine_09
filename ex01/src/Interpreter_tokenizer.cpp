/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter_tokenizer.cpp                          :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 20:20:26 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <algorithm>
#include "tokens/Number.h"
#include "tokens/Operator.h"
#include "tokens/Parenthesis.h"
#include "Interpreter.h"

Operator *tokenize_operator(char op) {
	return new Operator(op);
}

Parenthesis *tokenize_parenthesis(char brace) {
	if (brace == '(')
		return new Parenthesis(Token::ParenthesisOpen);
	else
		return new Parenthesis(Token::ParenthesisClose);
}
/**

    This function takes an unsigned integer i and a string input and attempts to
    extract a number starting from the index i in the input string.
    It creates a new Number object with the extracted number and returns a
    pointer to it. Basically, wrapper around atoi(), that allows represent
    "- 1" as (-1)
    @param i Unsigned integer reference indicating the starting index in the
    	input string
    @param input Constant reference to the input string
    @return Pointer to the newly created Number object
*/
Number *tokenize_number(unsigned int &i, const std::string &input) {
	bool negative = false;
	int result;

	if (input[i] == '-') {
		negative = true;
		i++;
	}
	while (input[i] == ' ')
		i++;
	result = std::atoi(input.data() + i);
	while (std::isdigit(input[i]))
		i++;
	i--;
	if (negative)
		result *= -1;
	return new Number(result);
}

/*
 *	This function is called if char on an index i is a negative sign ('-') an
 *	determines whether it is a minus operator or a negative sign of a
 *	following number.
 *	If it is, it checks the previous characters ignoring all spaces and
 *	closed braces. If the digit is found - treat as a unary operator and
 *	pushes an Operator(-) token to the tokens deque.
 *	Otherwise - treats as negative sign as part of the number and calls
 *	tokenize_number() to tokenize the negative number.
 */
void tokenize_negative(unsigned int &i, const std::string &input,
									std::deque<Token *> &tokens) {
	if (i > 0) {
		unsigned int j = i - 1;
		while (j > 0 && std::string(") ").find(input[j]) != kNotFound)
			--j;
		if (isdigit(input[j])) {
			tokens.push_back(tokenize_operator(input[i]));
		} else {
			tokens.push_back(tokenize_number(i, input));
		}
	} else {
		tokens.push_back(tokenize_number(i, input));
	}
}

// This function is responsible for breaking down the input expression into
// tokens and storing them in a deque. Each token represents an operator,
// operand, or parentheses. The tokens are later used to build a postfix
// expression which can be evaluated.
//
void Interpreter::make_tokens() {
	for (unsigned int i = 0; i < input_.size(); ++i) {
		if (std::string("()").find(input_[i]) != kNotFound) {
			tokens_.push_back(tokenize_parenthesis(input_[i]));
		} else if (input_[i] == '-') {
			tokenize_negative(i, input_, tokens_);
		} else if (std::isdigit(input_[i])) {
			tokens_.push_back(tokenize_number(i, input_));
		} else if (std::string("+/*-").find(input_[i]) != kNotFound) {
			tokens_.push_back(tokenize_operator(input_[i]));
		}
	}
}
