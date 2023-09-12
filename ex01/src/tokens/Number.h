/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Number.h                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 13:01:13 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX01_NUMBER_H
#define EX01_NUMBER_H


#include <ostream>
#include "Token.h"

class Number : public Token{
public:
	Number();
	Number(int i);
	Number(const Number &);
	Number &operator=(const Number &);

	std::ostream &operator<<(std::ostream &os) const ; /* override */
	bool operator==(const Number &rhs) const;
	bool operator!=(const Number &rhs) const;
	bool operator<(const Number &rhs) const;
	bool operator>(const Number &rhs) const;
	bool operator<=(const Number &rhs) const;
	bool operator>=(const Number &rhs) const;
	Number operator+(const Number &rhs) const;
	Number operator-(const Number &rhs) const;
	Number operator*(const Number &rhs) const;
	Number operator/(const Number &rhs) const;

	int GetNumber() const;

	~Number();

	Type GetType() const ; /* override */;
private:
	int number_;
};

#endif //EX01_NUMBER_H
