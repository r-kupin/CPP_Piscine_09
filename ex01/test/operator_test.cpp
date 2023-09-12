/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    operator_test.cpp                                  :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/13 14:05:13 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <gtest/gtest.h>
#include "../src/Interpreter.h"

TEST(OperatorTest, ConstructorTest) {
Operator op1('+');
EXPECT_EQ(op1.GetAnOperator(), '+');
EXPECT_EQ(op1.GetType(), Token::OperatorType);

Operator op2('-');
EXPECT_EQ(op2.GetAnOperator(), '-');
EXPECT_EQ(op2.GetType(), Token::OperatorType);
}

TEST(OperatorTest, OperatorAssignmentTest) {
Operator op1('+');
Operator op2('-');

op1 = op2;

EXPECT_EQ(op1.GetAnOperator(), '-');
EXPECT_EQ(op1.GetType(), Token::OperatorType);
}

TEST(OperatorTest, OperatorEqualsTest) {
Operator op1('+');
Operator op2('+');
Operator op3('-');

EXPECT_TRUE(op1 == op2);
EXPECT_FALSE(op1 == op3);
}

TEST(OperatorTest, OperatorNotEqualsTest) {
Operator op1('+');
Operator op2('+');
Operator op3('-');

EXPECT_FALSE(op1 != op2);
EXPECT_TRUE(op1 != op3);
}

TEST(OperatorTest, OperatorLessThanTest) {
Operator op1('+');
Operator op2('-');
Operator op3('*');
Operator op4('/');

EXPECT_TRUE(op2 < op3);
EXPECT_TRUE(op1 < op4);
}

TEST(OperatorTest, OperatorGreaterThanTest) {
Operator op1('+');
Operator op2('-');
Operator op3('*');
Operator op4('/');

EXPECT_TRUE(op3 > op2);
EXPECT_TRUE(op4 > op1);
}

TEST(OperatorTest, OperatorLessThanOrEqualTest) {
Operator op1('+');
Operator op2('-');
Operator op3('*');
Operator op4('/');

EXPECT_TRUE(op1 <= op2);
EXPECT_TRUE(op2 <= op3);
EXPECT_TRUE(op3 <= op4);
EXPECT_TRUE(op1 <= op1);
}

TEST(OperatorTest, OperatorGreaterThanOrEqualTest) {
Operator op1('+');
Operator op2('-');
Operator op3('*');
Operator op4('/');

EXPECT_TRUE(op4 >= op3);
EXPECT_TRUE(op3 >= op2);
EXPECT_TRUE(op2 >= op1);
EXPECT_TRUE(op1 >= op1);
}

TEST(OperatorTest, OperatorPerformTest) {
Number num1(5);
Number num2(2);
Operator op1('+');
Operator op2('*');

Number *result1 = op1.perform(num1, num2);
Number *result2 = op2.perform(num1, num2);

EXPECT_EQ(result1->GetNumber(), 7);
EXPECT_EQ(result2->GetNumber(), 10);

delete result1;
delete result2;
}