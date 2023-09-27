/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    main.cpp                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/20 21:10:32 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <fstream>
#include <iostream>
#include "BitcoinExchange.h"

bool open_files(std::ifstream &input, std::ifstream &data, std::string filename) {
	input.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	data.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try {
		input.open(filename.c_str());
		data.open(kDatabaseFile.c_str());
	} catch (const std::iostream::failure& e) {
		if (data.fail()) {
			std::cerr << "Error: Failed to open database file." <<
            kDatabaseFile << std::endl;
			input.close();
		} else {
			std::cerr << "Error: Failed to open input file." <<
            filename << std::endl;
		}
		return false;
	}
	return true;
}

bool read_db(std::ifstream &input, BitcoinExchange &be) {
	bool success = true;

	input.exceptions(std::ifstream::badbit);
	try {
		for (std::string line; getline(input, line); be.Insert(line));
	} catch (const std::iostream::failure& e) {
		std::cerr << "Error: Read failure." << std::endl;
		success = false;
	}
	input.clear();
	input.close();
    if (be.DBisEmpty()) {
        std::cerr << "Error: Empty file." << std::endl;
        success = false;
    }
	return success;
}

void read_process_input(std::ifstream &input, BitcoinExchange be) {
    input.exceptions(std::ifstream::badbit);
    try {
        for (std::string line; getline(input, line);) {
            if (!line.empty()) {
                try {
                    be.Querry(line);
                } catch (const BitcoinExchange::BadInputException &e) {
                    std::cerr << e.what() << line << std::endl;
                } catch (const BitcoinExchange::InputFileCorruptedException &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    } catch (const std::iostream::failure& e) {
        std::cerr << "Error: Read failure." << std::endl;
    }
    input.clear();
    input.close();
}

int main(int ac, char **av) {
    if (ac != 2) {
		std::cerr << "Error: wrong amount of arguments." << std::endl;
	} else {
 		std::ifstream input, data;

        if (open_files(input, data, av[1])) {
            BitcoinExchange be;
            bool input_read_success = read_db(data, be);
            if (!input_read_success) {
                data.clear();
                data.close();
            } else {
                try {
                    read_process_input(input, be);
                    return 0;
                } catch (const BitcoinExchange::DatabaseFileCorruptedError &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }
	return 1;
}
