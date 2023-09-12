/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    input_check_test.cpp                               :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/04 21:43:43 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <gtest/gtest.h>
#include "../src/Interpreter.h"

class empty_spaces_2_digit_one_operator
		: public ::testing::Test, public Interpreter {
public:
	empty_spaces_2_digit_one_operator() : Interpreter(" 1 + 1 ") {};
};

TEST_F(empty_spaces_2_digit_one_operator, empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class neg_1_empty_spaces_2_digit_one_operato
		: public ::testing::Test, public Interpreter {
public:
	neg_1_empty_spaces_2_digit_one_operato() : Interpreter(" -1 + 1 ") {};
};

TEST_F(neg_1_empty_spaces_2_digit_one_operato, neg_1_empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class neg_2_empty_spaces_2_digit_one_operato
		: public ::testing::Test, public Interpreter {
public:
	neg_2_empty_spaces_2_digit_one_operato() : Interpreter(" -1 + -1 ") {};
};

TEST_F(neg_2_empty_spaces_2_digit_one_operato, neg_2_empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class neg_3_empty_spaces_2_digit_one_operato
		: public ::testing::Test, public Interpreter {
public:
	neg_3_empty_spaces_2_digit_one_operato() : Interpreter(" -1 - -1 ") {};
};

TEST_F(neg_3_empty_spaces_2_digit_one_operato, neg_3_empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class neg_4_empty_spaces_2_digit_one_operato
		: public ::testing::Test, public Interpreter {
public:
	neg_4_empty_spaces_2_digit_one_operato() : Interpreter(" -1 - 1 ") {};
};

TEST_F(neg_4_empty_spaces_2_digit_one_operato, neg_4_empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class neg_5_empty_spaces_2_digit_one_operato
		: public ::testing::Test, public Interpreter {
public:
	neg_5_empty_spaces_2_digit_one_operato() : Interpreter(" 1 + -1 ") {};
};

TEST_F(neg_5_empty_spaces_2_digit_one_operato, neg_5_empty_spaces_2_digit_one_operator) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 0);
	EXPECT_EQ(GetOpenBraces(), 0);
	EXPECT_EQ(GetOperators(), 1);
}

class empty_parentesi
		: public ::testing::Test, public Interpreter {
public:
	empty_parentesi() : Interpreter(" 1() + 1 ") {};
};

TEST_F(empty_parentesi, empty_parentesis) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 1);
	EXPECT_EQ(GetOpenBraces(), 1);
	EXPECT_EQ(GetOperators(), 1);
}

class nested_parentesi
		: public ::testing::Test, public Interpreter {
public:
	nested_parentesi() : Interpreter(" ((1()) + 1) ") {};
};

TEST_F(nested_parentesi, nested_parentesis) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 3);
	EXPECT_EQ(GetOpenBraces(), 3);
	EXPECT_EQ(GetOperators(), 1);
}

class generic_parentesi
		: public ::testing::Test, public Interpreter {
public:
	generic_parentesi() : Interpreter(" (1 + 1) ") {};
};

TEST_F(generic_parentesi, generic_parentesis) {
	EXPECT_EQ(GetNumbers(), 2);
	EXPECT_EQ(GetCloseBraces(), 1);
	EXPECT_EQ(GetOpenBraces(), 1);
	EXPECT_EQ(GetOperators(), 1);
}

class subjec
		: public ::testing::Test, public Interpreter {
public:
	subjec() : Interpreter("3 + ((1 + 4) * 2) - 1") {};
};

TEST_F(subjec, subject) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_1
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_1() : Interpreter("-3 + ((1 + 4) * 2) - 1") {};
};

TEST_F(subject_negative_number_1, subject_negative_number_1 ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_1_braces
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_1_braces() : Interpreter("()-3 + ((1 + 4) * 2) - 1") {};
};

TEST_F(subject_negative_number_1_braces, subject_negative_number_1_braces ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 3);
	EXPECT_EQ(GetOpenBraces(), 3);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_2
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_2() : Interpreter("3 + ((-1 + 4) * 2) - 1") {};
};

TEST_F(subject_negative_number_2, subject_negative_number_2 ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_3
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_3() : Interpreter("3 + ((1 + -4) * 2) - 1") {};
};

TEST_F(subject_negative_number_3, subject_negative_number_3 ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_4
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_4() : Interpreter("3 + ((1 + 4) * -2) - 1") {};
};

TEST_F(subject_negative_number_4, subject_negative_number_4 ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class subject_negative_number_5
		: public ::testing::Test, public Interpreter {
public:
	subject_negative_number_5() : Interpreter("3 + ((1 + 4) * 2) - -1") {};
};

TEST_F(subject_negative_number_5, subject_negative_number_5 ) {
	EXPECT_EQ(GetNumbers(), 5);
	EXPECT_EQ(GetCloseBraces(), 2);
	EXPECT_EQ(GetOpenBraces(), 2);
	EXPECT_EQ(GetOperators(), 4);
}

class big_one
		: public ::testing::Test, public Interpreter {
public:
	big_one()
	: Interpreter("(4 + 6) * 3 - (-5 / 2) + 7 * (6 - 3) / (8 + 2) +"
					" (9 - 2 * (5 + 3)) * (12 - 4 * (7 - 5)) -"
					" 8 * 2 + 15 / 3") {};
};

TEST_F(big_one, big_one ) {
	EXPECT_EQ(GetNumbers(), 22);
	EXPECT_EQ(GetCloseBraces(), 8);
	EXPECT_EQ(GetOpenBraces(), 8);
	EXPECT_EQ(GetOperators(), 21);
}

TEST(CheckerTestWrong, empty) {
	EXPECT_THROW(Interpreter(""),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, only_minus) {
	EXPECT_THROW(Interpreter("-"),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, minus_one) {
	EXPECT_THROW(Interpreter(" -1"),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_space) {
	EXPECT_THROW(Interpreter(" "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces) {
	EXPECT_THROW(Interpreter("   "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces_one_digit) {
	EXPECT_THROW(Interpreter("  1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces_two_digit) {
	EXPECT_THROW(Interpreter(" 2 1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces_one_operator_one_digit) {
	EXPECT_THROW(Interpreter(" + 1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces_2_digit_2_operator) {
	EXPECT_THROW(Interpreter(" 1 + 1 + "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, empty_spaces_2_digit_2_operator_before) {
	EXPECT_THROW(Interpreter(" + 1 + 1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, wrong_parentesis_open) {
	EXPECT_THROW(Interpreter(" 1( + 1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, wrong_parentesis_closed) {
	EXPECT_THROW(Interpreter(" 1) + 1 "),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, subject_without_one_op ) {
	EXPECT_THROW(Interpreter("3 + ((1 + 4)  2) - 1"),
				 Interpreter::WrongInputException);
}

TEST(CheckerTestWrong, wrong_parentesis) {
	EXPECT_THROW(Interpreter(" 1)( + 1 "),
				 Interpreter::WrongInputException);
}
