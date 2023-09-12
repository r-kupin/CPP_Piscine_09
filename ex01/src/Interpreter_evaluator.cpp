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

void print_stack(MutantStack<Number *> &calc_stack) {
	std::cout << "| ST";
	for (MutantStack<Number *>::reverse_iterator iterator = calc_stack.rbegin();
			iterator != calc_stack.rend();
			++iterator) {
		std::cout << " " << (*iterator)->GetNumber();
	}
	std::cout << "]" << std::endl;
}

void perform_operation(Operator *front_op, MutantStack<Number*> &calc_stack) {
	Number *op1, *op2;

	op2 = dynamic_cast<Number*>(calc_stack.top());
	calc_stack.pop();
	op1 = dynamic_cast<Number*>(calc_stack.top());
	calc_stack.pop();
	calc_stack.push(front_op->perform(*op1, *op2));
	delete op1;
	delete op2;
	delete front_op;
}

int Interpreter::evaluate() {
	MutantStack<Number *> calc_stack;
	int result;

	for (Token *front = tokens_.front(); !tokens_.empty();
		 tokens_.pop_front(), front = tokens_.front()) {
		front->operator<<(std::cout << "I ") << " | OP ";
		if (front->GetType() == Token::NumberType) {
			std::cout << "Push ";
			calc_stack.push(dynamic_cast<Number*>(front));
		} else {
			perform_operation(dynamic_cast<Operator*>(front), calc_stack);
		}
		print_stack(calc_stack);
	}
	result = calc_stack.top()->GetNumber();
	delete calc_stack.top();
	return result;
}