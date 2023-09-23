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

#include <cstdlib>
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

Date::Date(const std::string &date_str)
: year_(std::atoi(date_str.substr(0, date_str.find_first_of('-')).c_str())),
	month_(std::atoi(date_str.substr(date_str.find_first_of('-') + 1, date_str.find_last_of('-')).c_str())),
	day_(std::atoi(date_str.substr(date_str.find_last_of('-') + 1, 0).c_str())) {}

bool Date::IsCorrectDataString(const std::string &str) {
	int separators = 0;
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if ((*it) == '-') {
			separators++;
		} else if (!std::isdigit(*it)) {
			return false;
		}
	}
	if (separators != 2)
		return false;
	int year = std::atoi(str.substr(0, str.find_first_of('-')).c_str());
	int month = std::atoi(str.substr(str.find_first_of('-') + 1, str.find_last_of('-')).c_str());
	int day = std::atoi(str.substr(str.find_last_of('-') + 1, 0).c_str());
	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	/**
		Check for leap year and update February's days
		year % 4 == 0: This part checks if the year is divisible by 4. If a year is divisible by 4, it's a candidate for being a leap year. This is because leap years occur every 4 years.
		year % 100 != 0: This part checks if the year is not divisible by 100. Years divisible by 100 are usually not leap years, unless they are also divisible by 400. For example, the year 1900 is divisible by 4 and 100, but it's not a leap year because it's not divisible by 400.
		year % 400 == 0: This part checks if the year is divisible by 400. If a year is divisible by 400, it is considered a leap year, even if it's divisible by 100. This exception to the rule is to keep the calendar synchronized with the Earth's orbit more accurately.
	*/
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		daysInMonth[2] = 29;
	}

	return day <= daysInMonth[month];
}

Date::~Date() {

}

bool Date::operator<(const Date &rhs) const {
	if (year_ < rhs.year_)
		return true;
	if (rhs.year_ < year_)
		return false;
	if (month_ < rhs.month_)
		return true;
	if (rhs.month_ < month_)
		return false;
	return day_ < rhs.day_;
}

bool Date::operator>(const Date &rhs) const {
	return rhs < *this;
}

bool Date::operator<=(const Date &rhs) const {
	return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const {
	return !(*this < rhs);
}
