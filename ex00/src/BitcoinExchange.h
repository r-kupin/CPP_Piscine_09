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

	BitcoinExchange &operator=(const BitcoinExchange &);

    ~BitcoinExchange();

    void setDbFormat(const std::string &dbFormat);
    void setInputFormat(const std::string &inputFormat);

    void Querry(const std::string &str);
    void Insert(const std::string &str);

    bool DBisEmpty() const;

    static std::string GetDelimiter(const std::string &first_line,
                                    std::string before, std::string after);
private:
    std::string db_delimiter_;
    std::string imp_delimiter_;
	std::map<Date, float> table_;
};


#endif //EX00_BITCOINEXCHANGE_H