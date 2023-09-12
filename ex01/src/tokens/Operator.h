/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Operator.h                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/09 17:21:39 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX01_OPERATOR_H
#define EX01_OPERATOR_H


#include "Token.h"
#include "Number.h"

class Operator : public Token{
public:
	Operator();
	Operator(const Operator &);
	explicit Operator(char an_operator);
	Operator &operator=(const Operator &);

	std::ostream &operator<<(std::ostream &os) const ; /* override */
	bool operator==(const Operator &rhs) const;
	bool operator!=(const Operator &rhs) const;
	bool operator<(const Operator &rhs) const;
	bool operator>(const Operator &rhs) const;
	bool operator<=(const Operator &rhs) const;
	bool operator>=(const Operator &rhs) const;

	Number *perform(const Number &n1, const Number &n2) const;

	~Operator();

	Type GetType() const ; /* override */
	char GetAnOperator() const;
private:
	char	operator_;
	int		priority_;
};


#endif //EX01_OPERATOR_H
