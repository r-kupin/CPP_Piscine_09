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

void spot_braces(char check, int& close_braces, int& open_braces) {
	if (check == ')')
		close_braces++;
	if (check == '(')
		open_braces++;
}

void handle_negatives(unsigned int i, const std::string& input,
					  int& operators) {
	if (input[i] == '-' && i > 1) {
		unsigned int j = i - 1;
		while (j > 0 && std::string(") ").find(input[j]) != kNotFound)
			--j;
		if (std::isdigit(input[j]))
			operators++;
	}
}

void handle_operators(unsigned int i, const std::string& input,
					  int& operators) {
	if (std::string("+*/").find(input[i]) != kNotFound)
		operators++;
}

void handle_digits(unsigned int &i, const std::string& input, int& numbers) {
	if (std::isdigit(input[i])) {
		while (std::isdigit(input[i]))
			++i;
		numbers++;
	}
}

/*
 * This function checks if the input string is syntactically correct by
 * performing a series of checks on the input expression. The function returns a
 * boolean value indicating whether the input is correct or not.
 * Counts operators, numbers and braces
 * checks the basic constraints:
 * 	amount of open and closed braces must be equal
 * 	amount of closed braces should never be bigger amount of open braces
 * 	amount of operators mustbe equal to amount of numbers - 1
 */
bool Interpreter::InputIsCorrect() {
	for (unsigned int i = 0; i < input_.size(); ++i) {
		handle_operators(i, input_, operators_);
		handle_negatives(i, input_, operators_);
		handle_digits(i, input_, numbers_);
		spot_braces(input_[i], close_braces_, open_braces_);
		if (close_braces_ > open_braces_)
			return false;
	}
	if (close_braces_ != open_braces_ ||
		!operators_ ||
		numbers_ != (operators_ + 1))
		return false;
	return true;
}