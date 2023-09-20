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
#include "Interpreter.h"

Operator *tokenize_operator(char op) {
	return new Operator(op);
}

/**
 *   This function takes an unsigned integer i and a string input and
 *   attempts to
 *   extract a number starting from the index i in the input string.
 *   It creates a new Number object with the extracted number and returns a
 *   pointer to it. Basically, wrapper around atoi()
 *   @param i Unsigned integer reference indicating the starting index in the
 *   	input string
 *   @param input Constant reference to the input string
 *   @return Pointer to the newly created Number object
 */
Number *tokenize_number(unsigned int &i, const std::string &input) {
	int result;

	while (input[i] == ' ')
		i++;
	result = std::atoi(input.data() + i);
	while (std::isdigit(input[i]))
		i++;
	i--;

	return new Number(result);
}

/**
 * This function is responsible for breaking down the input expression into
 * tokens and storing them in a deque. Each token represents an operator,
 * operand, or parentheses. The tokens are later used to build a postfix
 * expression which can be evaluated.
 */
void Interpreter::make_tokens() {
	for (unsigned int i = 0; i < input_.size(); ++i) {
        if (std::isdigit(input_[i])) {
			tokens_.push_back(tokenize_number(i, input_));
		} else if (std::string("+/*-").find(input_[i]) != kNotFound) {
			tokens_.push_back(tokenize_operator(input_[i]));
		}
	}
}
