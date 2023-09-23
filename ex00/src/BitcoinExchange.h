/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    BitcoinExchange.h                                  :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/20 21:13:32 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX00_BITCOINEXCHANGE_H
#define EX00_BITCOINEXCHANGE_H


#include <string>
#include <map>
#include "Date.h"

static const std::string kDatabaseFile = "resources/data.csv";

class BitcoinExchange {
public:

	class DatabaseFileCorruptedError : public std::exception {
	public:
		const char *what() const throw();
	};

	class InputFileCorruptedException : public std::exception {};

	class NegativeNumberException : public InputFileCorruptedException {
	public:
		const char *what() const throw();
	};
	class TooBigNumberException : public InputFileCorruptedException {
	public:
		const char *what() const throw();
	};
	class BadInputException : public InputFileCorruptedException {
	public:
		const char *what() const throw();
	};

    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange &);

	BitcoinExchange(std::vector<std::string> db, const std::string &delimiter);

	BitcoinExchange &operator=(const BitcoinExchange &);

    ~BitcoinExchange();

    std::string Querry(const std::string &str, const std::string &delimiter);

private:
	std::map<Date, float> table_;
};


#endif //EX00_BITCOINEXCHANGE_H