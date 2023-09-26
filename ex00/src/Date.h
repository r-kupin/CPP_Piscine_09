/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    Date.h                                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/20 21:41:38 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX00_LIB_DATE_H
#define EX00_LIB_DATE_H


#include <string>
#include <ostream>

class Date {
public:
    bool operator==(const Date &rhs) const;

    bool operator!=(const Date &rhs) const;

public:
	static bool IsCorrectDataString(const std::string &str);

    Date();

    Date(const Date &);

	Date(const std::string &date_str);

	Date &operator=(const Date &);

    ~Date();

	bool operator<(const Date &rhs) const;

	bool operator>(const Date &rhs) const;

	bool operator<=(const Date &rhs) const;

	bool operator>=(const Date &rhs) const;

    int getYear() const;

    int getMonth() const;

    int getDay() const;

private:
	int year_;
	int month_;
	int day_;
};

std::ostream &operator<<(std::ostream &os, const Date &date);

#endif //EX00_LIB_DATE_H