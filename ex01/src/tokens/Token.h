/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Token.h                                            :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/04 17:16:45 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX01_TOKEN_H
#define EX01_TOKEN_H


#include <ostream>

class Token {
public:

	class WrongOperatorException : public std::exception {
	public:
		const char *what() const throw(); /* override */
	};

	enum Type {
		NumberType,
		OperatorType,
		ParenthesisOpen,
		ParenthesisClose
	};

	Token() {};
	explicit Token(Type type) : type_(type) {}

	virtual std::ostream &operator<<(std::ostream &os) const = 0;

	virtual Type GetType() const = 0;

	virtual ~Token() {};
protected:
	Type type_;
};

#endif //EX01_TOKEN_H
