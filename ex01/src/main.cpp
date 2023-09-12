/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    main.cpp                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/04 16:06:11 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <cassert>
#include <string>
#include <iostream>
#include "Interpreter.h"

int main(int ac, char **av) {
	assert(ac == 2 && "There should be only 1 argument, which is expression");
	std::string expression(av[1]);
	Interpreter tokens(expression);
	tokens.make_tokens();
	std::cout << "Tokens: " <<  tokens << " " << std::endl;
	tokens.make_postfix();
	std::cout << "Postfix: " <<  tokens << " " << std::endl;
	std::cout << "Result : " << tokens.evaluate() << std::endl;
	return 0;
}