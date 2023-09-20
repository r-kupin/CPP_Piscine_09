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
	assert(ac == 2 && "There should be only 1 argument, which is an RPN"
                      "expression");
	std::string expression(av[1]);
    try {
        Interpreter tokens(expression);
        tokens.make_tokens();
        if (PRINT)
            std::cout << "Tokens: " << tokens << " " << std::endl;
        std::cout << tokens.evaluate() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
	return 0;
}