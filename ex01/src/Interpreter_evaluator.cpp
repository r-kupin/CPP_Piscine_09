/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter_evaluator.cpp                          :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/12 16:03:51 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <iostream>
#include <vector>
#include "Interpreter.h"

void print_stack(MutantStack<Number> &calc_stack) {
	std::cout << "| ST";
	for (MutantStack<Number>::reverse_iterator iterator = calc_stack.rbegin();
			iterator != calc_stack.rend();
			++iterator) {
		std::cout << " " << (*iterator).GetNumber();
	}
	std::cout << "]" << std::endl;
}

bool perform_operation(const Operator& front_op, MutantStack<Number> &calc_stack) {
    Number op2, op1;
    if (!calc_stack.empty()) {
        op2 = calc_stack.top();
        calc_stack.pop();
    } else {
        return false;
    }
    if (!calc_stack.empty()) {
        op1 = calc_stack.top();
        calc_stack.pop();
    } else {
        return false;
    }
    calc_stack.push(front_op.perform(op1, op2));
	return true;
}

int Interpreter::evaluate() {
	int result;
    MutantStack<Number> calc_stack;

	for (Token *front = *tokens_.begin(); !tokens_.empty();
		tokens_.pop_front(), front = *tokens_.begin()) {
		if (PRINT)
			front->operator<<(std::cout << "I ") << " | OP ";
		if (front->GetType() == Token::NumberType) {
			if (PRINT)
				std::cout << "Push ";
			calc_stack.push(*dynamic_cast<Number *>(front));
		} else {
			if (!perform_operation(*dynamic_cast<Operator *>(front),
								   calc_stack))
				throw WrongInputException();
		}
        if (PRINT)
            print_stack(calc_stack);
		delete front;
	}
	result = calc_stack.top().GetNumber();
	return result;
}