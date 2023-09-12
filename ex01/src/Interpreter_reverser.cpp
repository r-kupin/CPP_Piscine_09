/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Interpreter_reverser.cpp                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 23:34:57 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Interpreter.h"

static void push_operator_to_opers(MutantStack<Operator *> &operators,
									Operator *front_op) {
	if (operators.empty() || *front_op > *operators.top()) {
		operators.push(front_op);
	}
}

static void dump_opers_w_hi_eq_prior(MutantStack<Operator *> &operators,
									 std::deque<Token *> &postfixed,
									 const Operator *token_front) {
	while (!operators.empty() && *token_front <= *operators.top()) {
		postfixed.push_back(operators.top());
		operators.pop();
	}
}

static void push_open_brace_to_opers(MutantStack<Operator *> &operators,
							  		const Token *front) {
	delete front;
	operators.push(new Operator('('));
}

static void dump_opers_to_open_brace(MutantStack<Operator *> &operators,
							  		std::deque<Token *> &postfixed,
							  		const Token *front) {
	delete front;
	while (*operators.top() != Operator('(')) {
		postfixed.push_back(operators.top());
		operators.pop();
	}
	delete operators.top();
	operators.pop();
}

static void dump_opers_stack_leftovers(MutantStack<Operator *> &operators,
										std::deque<Token *> &postfixed) {
	while (!operators.empty()) {
		postfixed.push_back(operators.top());
		operators.pop();
	}
}

/*
 * This function converts the infix expression into a postfix expression using
 * the Shunting Yard algorithm.
 *
 *    Initialize an empty stack for operators and an empty queue for output.
 *    Loop through each token in the input token queue:
 *    - If the token is a number, add it to the output queue.
 *    - If the token is a left parenthesis, push it onto the operator stack.
 *    - If the token is a right parenthesis, pop operators from the operator
 *    	stack and add them to the output queue until a left parenthesis is
 *    	encountered. Discard the left parenthesis.
 *    - If the token is an operator:
 *    		- While the operator stack is not empty and the top operator has
 *    		higher precedence or equal precedence and is left-associative,
 *    		pop the top operator and add it to the output queue.
 *    		- Push the token onto the operator stack.
 *    Pop any remaining operators from the operator stack and add them to the
 *    output queue.
 *    Return the postfix token queue.
 */
void Interpreter::make_postfix() {
	MutantStack<Operator *> operators;
	std::deque<Token *> postfixed;

	for (Token *front = tokens_.front();
		 !tokens_.empty();
		 tokens_.pop_front(), front = tokens_.front()) {
		if (front->GetType() == Token::NumberType) {
			postfixed.push_back(front);
		} else if (front->GetType() == Token::OperatorType) {
			Operator* front_op = dynamic_cast<Operator*>(front);
			dump_opers_w_hi_eq_prior(operators, postfixed, front_op);
			push_operator_to_opers(operators, front_op);
		} else if (front->GetType() == Token::ParenthesisOpen) {
			push_open_brace_to_opers(operators, front);
		} else if (front->GetType() == Token::ParenthesisClose) {
			dump_opers_to_open_brace(operators, postfixed, front);
		}
	}
	dump_opers_stack_leftovers(operators, postfixed);
	tokens_ = postfixed;
}