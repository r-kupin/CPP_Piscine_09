/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    postfixer_test.cpp                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/12 23:40:47 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <gtest/gtest.h>
#include "../src/Interpreter.h"

class one_plus_one_postfix : public ::testing::Test, public Interpreter {
public:
	one_plus_one_postfix() : Interpreter("1 + 1") {};
protected:
	Number one = Number(1);
	Operator plus = Operator('+');

	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		make_postfix();
		deque = GetTokens();
	}
};

TEST_F(one_plus_one_postfix, one_plus_one_postfix) {
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[1]));
	EXPECT_EQ(plus, *dynamic_cast<Operator*>(deque[2]));
	EXPECT_EQ(evaluate(), 2);
}

class nested_parenthesis_postfix : public ::testing::Test, public Interpreter {
public:
	nested_parenthesis_postfix() : Interpreter(" ((1()) + 1) ") {};
protected:
	Number one = Number(1);
	Operator plus = Operator('+');

	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		make_postfix();
		deque = GetTokens();
	}
};

TEST_F(nested_parenthesis_postfix, nested_parenthesis_postfix) {
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[1]));
	EXPECT_EQ(plus, *dynamic_cast<Operator*>(deque[2]));
	EXPECT_EQ(evaluate(), 2);
}

class subject_postfix : public ::testing::Test, public Interpreter {
public:
	subject_postfix() : Interpreter(" 3 + ((1 + 4) * 2) - 1 ") {};
protected:
	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		make_postfix();
		deque = GetTokens();
	}
};

TEST_F(subject_postfix, subject_postfix) {
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(Number(1), *dynamic_cast<Number*>(deque[1]));
	EXPECT_EQ(Number(4), *dynamic_cast<Number*>(deque[2]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[3]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[4]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[5]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[6]));
	EXPECT_EQ(Number(1), *dynamic_cast<Number*>(deque[7]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[8]));
	EXPECT_EQ(evaluate(), 12);
}


class big_expression : public ::testing::Test, public Interpreter {
public:
	big_expression()
	: Interpreter("(4 + 6) * 3 - (-5 / 2) + 7 * (6 - 3) / (8 + 2) +"
				  " (9 - 2 * (5 + 3)) * (12 - 4 * (7 - 5)) -"
				  " 8 * 2 + 15 / 3") {};
protected:
	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		make_postfix();
		deque = GetTokens();
	}
};

TEST_F(big_expression, big_expression) {
	EXPECT_EQ(Number(4), *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(Number(6), *dynamic_cast<Number*>(deque[1]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[2]));
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[3]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[4]));
	EXPECT_EQ(Number(-5), *dynamic_cast<Number*>(deque[5]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[6]));
	EXPECT_EQ(Operator('/'), *dynamic_cast<Operator*>(deque[7]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[8]));
	EXPECT_EQ(Number(7), *dynamic_cast<Number*>(deque[9]));
	EXPECT_EQ(Number(6), *dynamic_cast<Number*>(deque[10]));
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[11]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[12]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[13]));
	EXPECT_EQ(Number(8), *dynamic_cast<Number*>(deque[14]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[15]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[16]));
	EXPECT_EQ(Operator('/'), *dynamic_cast<Operator*>(deque[17]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[18]));
	EXPECT_EQ(Number(9), *dynamic_cast<Number*>(deque[19]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[20]));
	EXPECT_EQ(Number(5), *dynamic_cast<Number*>(deque[21]));
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[22]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[23]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[24]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[25]));
	EXPECT_EQ(Number(12), *dynamic_cast<Number*>(deque[26]));
	EXPECT_EQ(Number(4), *dynamic_cast<Number*>(deque[27]));
	EXPECT_EQ(Number(7), *dynamic_cast<Number*>(deque[28]));
	EXPECT_EQ(Number(5), *dynamic_cast<Number*>(deque[29]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[30]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[31]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[32]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[33]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[34]));
	EXPECT_EQ(Number(8), *dynamic_cast<Number*>(deque[35]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[36]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[37]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[38]));
	EXPECT_EQ(Number(15), *dynamic_cast<Number*>(deque[39]));
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[40]));
	EXPECT_EQ(Operator('/'), *dynamic_cast<Operator*>(deque[41]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[42]));
	EXPECT_EQ(evaluate(), -5);
}
