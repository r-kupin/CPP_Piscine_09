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

#include <cstdlib>
#include <iostream>
#include "BitcoinExchange.h"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
: table_(other.table_){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this == &other)
        return *this;
    table_ = other.table_;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::GetDelimiter(const std::string &first_line,
                                          std::string before,
                                          std::string after) {
    if (first_line.find(before) == 0 &&
        first_line.find(after) != std::string::npos) {
        return first_line.substr(before.size(),
                                 first_line.size() - (before.size() + after.size()));
    } else
        return "";
}

void BitcoinExchange::Insert(const std::string &str) {
    if (!str.empty()) {
        if (db_delimiter_.empty()) {
            db_delimiter_ = GetDelimiter(str, "date", "exchange_rate");
            if (db_delimiter_.empty())
                throw DatabaseFileCorruptedError();
        } else {
            unsigned long delim_pos = str.find_first_of(db_delimiter_);
            std::string date_str = str.substr(0, delim_pos);
            std::string val_str = str.substr(delim_pos + db_delimiter_.length());
            double value = std::atof(val_str.c_str());

            if (date_str.empty() || val_str.empty() ||
                !Date::IsCorrectDataString(date_str) ||
                value < 0)
                throw DatabaseFileCorruptedError();

            table_.insert(std::pair<Date, float>(Date(date_str), value));
        }
    }
}

void BitcoinExchange::Querry(const std::string &str) {
	if (!str.empty()) {
		if (imp_delimiter_.empty()) {
			imp_delimiter_ = GetDelimiter(str, "date", "value");
			if (imp_delimiter_.empty())
				throw DatabaseFileCorruptedError();
		} else {
			unsigned long delim_pos = str.find_first_of(imp_delimiter_);
			std::string date_str = str.substr(0, delim_pos);
			std::string amount_str = str.substr(delim_pos + imp_delimiter_.length());
			double amount = std::atof(amount_str.c_str());

			if (date_str.empty() || amount_str.empty() ||
				!Date::IsCorrectDataString(date_str))
				throw BadInputException();
			if (amount > 1000)
				throw TooBigNumberException();
			if (amount < 0)
				throw NegativeNumberException();
			Date lookup(date_str);
			if (table_.begin()->first > lookup)
				throw BadInputException();
			std::map<Date, float>::iterator closest_date_it =
					table_.lower_bound(lookup);
			if (closest_date_it == table_.end() || closest_date_it->first != lookup)
				--closest_date_it;
			double value = (*closest_date_it).second * amount;
			std::cout << date_str << " => " << amount_str << " = " << value << std::endl;
		}
	}
}

bool BitcoinExchange::DBisEmpty() const {
    return table_.empty();
}

const char *BitcoinExchange::DatabaseFileCorruptedError::what() const throw() {
	return "Error: database file corrupted.";
}

const char *BitcoinExchange::NegativeNumberException::what() const throw() {
	return "Error: not a positive number.";
}

const char *BitcoinExchange::TooBigNumberException::what() const throw() {
	return "Error: too large a number.";
}

const char *BitcoinExchange::BadInputException::what() const throw() {
	return "Error: bad input => ";
}
