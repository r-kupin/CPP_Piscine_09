/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Date.cpp                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/20 21:41:38 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include "Date.h"


Date::Date() {

}

Date::Date(const Date &other) {

}

Date &Date::operator=(const Date &other) {
    if (this == &other)
        return *this;
    return *this;
}

Date::~Date() {

}

bool Date::IsCorrectDataString(const std::string &str) {
	return false;
}
