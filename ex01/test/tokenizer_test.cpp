/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    tokenizer_test.cpp                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/12 20:24:58 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <gtest/gtest.h>
#include "../src/Interpreter.h"

class one_plus_one_tokenizer : public ::testing::Test, public Interpreter {
public:
	one_plus_one_tokenizer() : Interpreter("1 + 1") {};
protected:
	Number one = Number(1);
	Operator plus = Operator('+');

	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		deque = GetTokens();
	}
};

TEST_F(one_plus_one_tokenizer, one_plus_one_tokenizer_creation) {
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(plus, *dynamic_cast<Operator*>(deque[1]));
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[2]));
}

TEST_F(one_plus_one_tokenizer, one_plus_one_tokenizer_content) {
	EXPECT_EQ(one.GetNumber(), 1);
	EXPECT_EQ(one.GetType(), Token::NumberType);
	EXPECT_EQ(plus.GetAnOperator(), '+');
	EXPECT_EQ(plus.GetType(), Token::OperatorType);
}


class minus_1_plus_1 : public ::testing::Test, public Interpreter {
public:
	minus_1_plus_1 () : Interpreter(" -1 + 1 ") {};
protected:
	Number m_one = Number(-1);
	Number one = Number(1);
	Operator plus = Operator('+');

	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		deque = GetTokens();
	}
};

TEST_F(minus_1_plus_1 , minus_1_plus_1_creation) {
	EXPECT_EQ(*dynamic_cast<Number*>(deque[0]), m_one);
	EXPECT_NE(*dynamic_cast<Number*>(deque[0]), one);
	EXPECT_EQ(*dynamic_cast<Operator*>(deque[1]), plus);
	EXPECT_EQ(*dynamic_cast<Number*>(deque[2]), one);
}

TEST_F(minus_1_plus_1 , minus_1_plus_1_content) {
	EXPECT_EQ(m_one.GetNumber(), -1);
	EXPECT_EQ(m_one.GetType(), Token::NumberType);
}

class nested_parenthesis : public ::testing::Test, public Interpreter {
public:
	nested_parenthesis() : Interpreter(" ((1()) + 1) ") {};
protected:
	Number one = Number(1);
	Operator plus = Operator('+');
	Parenthesis open = Parenthesis(Token::Type::ParenthesisOpen);
	Parenthesis close = Parenthesis(Token::Type::ParenthesisClose);

	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		deque = GetTokens();
	}
};

TEST_F(nested_parenthesis, nested_parenthesis_creation) {
	EXPECT_EQ(open, *dynamic_cast<Parenthesis*>(deque[0]));
	EXPECT_EQ(open, *dynamic_cast<Parenthesis*>(deque[1]));
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[2]));
	EXPECT_EQ(open, *dynamic_cast<Parenthesis*>(deque[3]));
	EXPECT_EQ(close, *dynamic_cast<Parenthesis*>(deque[4]));
	EXPECT_EQ(close, *dynamic_cast<Parenthesis*>(deque[5]));
	EXPECT_EQ(plus, *dynamic_cast<Operator*>(deque[6]));
	EXPECT_EQ(one, *dynamic_cast<Number*>(deque[7]));
	EXPECT_EQ(close, *dynamic_cast<Parenthesis*>(deque[8]));
}


class subject_tokenized : public ::testing::Test, public Interpreter {
public:
	subject_tokenized() : Interpreter(" 3 + ((1 + 4) * 2) - 1 ") {};
protected:
	std::deque<Token *> deque;

	virtual void SetUp() {
		make_tokens();
		deque = GetTokens();
	}
};

TEST_F(subject_tokenized, nested_parenthesis_creation) {
	EXPECT_EQ(Number(3), *dynamic_cast<Number*>(deque[0]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[1]));
	EXPECT_EQ(Parenthesis(Token::Type::ParenthesisOpen),
			  							*dynamic_cast<Parenthesis*> (deque[2]));
	EXPECT_EQ(Parenthesis(Token::Type::ParenthesisOpen),
			  							*dynamic_cast<Parenthesis*> (deque[3]));
	EXPECT_EQ(Number(1), *dynamic_cast<Number*>(deque[4]));
	EXPECT_EQ(Operator('+'), *dynamic_cast<Operator*>(deque[5]));
	EXPECT_EQ(Number(4), *dynamic_cast<Number*>(deque[6]));
	EXPECT_EQ(Parenthesis(Token::Type::ParenthesisClose),
					  					*dynamic_cast<Parenthesis*> (deque[7]));
	EXPECT_EQ(Operator('*'), *dynamic_cast<Operator*>(deque[8]));
	EXPECT_EQ(Number(2), *dynamic_cast<Number*>(deque[9]));
	EXPECT_EQ(Parenthesis(Token::Type::ParenthesisClose),
			  							*dynamic_cast<Parenthesis*>(deque[10]));
	EXPECT_EQ(Operator('-'), *dynamic_cast<Operator*>(deque[11]));
	EXPECT_EQ(Number(1), *dynamic_cast<Number*>(deque[12]));
}

