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

class Date {
public:
	static bool IsCorrectDataString(const std::string &str);

    Date();

    Date(const Date &);

	Date(const std::string &basicString);

	Date &operator=(const Date &);

    ~Date();

private:
};


#endif //EX00_LIB_DATE_H