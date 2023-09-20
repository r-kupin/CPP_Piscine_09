/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter_input_checker.cpp                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 22:54:22 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Interpreter.h"

void handle_operators(unsigned int i, const std::string& input,
					  int& operators) {
	if (std::string("+*/-").find(input[i]) != kNotFound)
		operators++;
}

void handle_digits(unsigned int &i, const std::string& input, int& numbers) {
	if (std::isdigit(input[i])) {
		while (std::isdigit(input[i]))
			++i;
		numbers++;
	}
}

bool Interpreter::InputIsCorrect() {
	for (unsigned int i = 0; i < input_.size(); ++i) {
		handle_operators(i, input_, operators_);
		handle_digits(i, input_, numbers_);
	}
	if (!operators_ || numbers_ != (operators_ + 1))
		return false;
	return true;
}