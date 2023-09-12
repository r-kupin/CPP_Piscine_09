/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    number_test.cpp                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/03/13 13:58:37 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <gtest/gtest.h>
#include "../src/Interpreter.h"

TEST(NumberTest, OperatorEqual) {
	Number n1(10);
	Number n2(10);
	EXPECT_TRUE(n1 == n2);
}

TEST(NumberTest, OperatorNotEqual) {
	Number n1(10);
	Number n2(20);
	EXPECT_TRUE(n1 != n2);
}

TEST(NumberTest, OperatorLessThan) {
	Number n1(10);
	Number n2(20);
	EXPECT_TRUE(n1 < n2);
}

TEST(NumberTest, OperatorGreaterThan) {
	Number n1(20);
	Number n2(10);
	EXPECT_TRUE(n1 > n2);
}

TEST(NumberTest, OperatorLessThanOrEqual) {
	Number n1(10);
	Number n2(20);
	Number n3(10);
	EXPECT_TRUE(n1 <= n2);
	EXPECT_TRUE(n1 <= n3);
}

TEST(NumberTest, OperatorGreaterThanOrEqual) {
	Number n1(20);
	Number n2(10);
	Number n3(20);
	EXPECT_TRUE(n1 >= n2);
	EXPECT_TRUE(n1 >= n3);
}

TEST(NumberTest, OperatorAdd) {
	Number n1(10);
	Number n2(20);
	Number n3 = n1 + n2;
	EXPECT_EQ(n3.GetNumber(), 30);
}

TEST(NumberTest, OperatorSubtract) {
	Number n1(20);
	Number n2(10);
	Number n3 = n1 - n2;
	EXPECT_EQ(n3.GetNumber(), 10);
}
