/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    BitcoinExchange.cpp                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/20 21:13:32 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <vector>
#include <cstdlib>
#include <sstream>
#include "BitcoinExchange.h"

BitcoinExchange::BitcoinExchange() {}


BitcoinExchange::BitcoinExchange(std::vector<std::string> db) {
	for (std::vector<std::string>::iterator it = db.begin(); it != db.end(); ++it) {
		unsigned long comma_pos = (*it).find(',');
		std::string date_str = (*it).substr(0, comma_pos);
		std::string val_str((*it).c_str() + comma_pos);
		double value = std::strtod((*it).c_str() + comma_pos, NULL);
		
		if (date_str.empty() || val_str.empty() || !Date::IsCorrectDataString(date_str) ||
			value > 1000 || value < 0)
			throw DatabaseFileCorruptedError();
		
		table_.insert(std::pair<Date, float>(Date(date_str), value));
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this == &other)
        return *this;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::Querry(const std::string &str, const std::string &delimiter) {
	unsigned long delim_pos = str.find(delimiter);
	std::string date_str = str.substr(0, delim_pos);
	std::string amount_str(str.c_str() + delim_pos + delimiter.size());
	double amount = std::strtod(str.c_str() + delim_pos, NULL);

	if (date_str.empty() || amount_str.empty() || !Date::IsCorrectDataString(date_str))
		throw BadInputException();
	if (amount > 1000)
		throw TooBigNumberException();
	if (amount < 0)
		throw NegativeNumberException();
	const std::map<Date, float>::iterator &closest_date_it = table_.lower_bound(Date(date_str));
	double value = (*closest_date_it).second * amount;
	std::ostringstream os;
	os << date_str << " => " << amount_str << " = " << value;
	return  os.str();
}

const char *BitcoinExchange::DatabaseFileCorruptedError::what() const {
	return "Error: database file corrupted.";
}

const char *BitcoinExchange::NegativeNumberException::what() const {
	return "Error: not a positive number.";
}

const char *BitcoinExchange::TooBigNumberException::what() const {
	return "Error: too large a number.";
}

const char *BitcoinExchange::BadInputException::what() const {
	return "Error: bad input => ";
}
