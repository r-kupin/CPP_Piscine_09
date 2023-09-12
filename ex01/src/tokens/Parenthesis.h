/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Parenthesis.h                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 18:21:44 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX01_PARENTHESIS_H
#define EX01_PARENTHESIS_H


#include "Token.h"

class Parenthesis : public Token {
public:
	Parenthesis();
	Parenthesis(const Parenthesis &);
	explicit Parenthesis(Type type);
	Parenthesis &operator=(const Parenthesis &);
	bool operator==(const Parenthesis &rhs) const;

	~Parenthesis();

	std::ostream &operator<<(std::ostream &os) const ; /* override */

	Type GetType() const ; /* override */
};


#endif //EX01_PARENTHESIS_H
