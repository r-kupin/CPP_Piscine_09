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
#include <vector>
#include "BitcoinExchange.h"

bool open_files(std::ifstream &input, std::ifstream &data, std::string filename) {
	input.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	data.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try {
		input.open(filename.c_str());
		data.open(kDatabaseFile.c_str());
	} catch (const std::iostream::failure& e) {
		if (data.fail()) {
			std::cerr << "Error: Failed to open database file." << kDatabaseFile << std::endl;
			input.close();
		} else {
			std::cerr << "Error: Failed to open input file." << filename << std::endl;
		}
		return false;
	}
	return true;
}

bool read_from_file(std::ifstream &input, std::vector<std::string> &db) {
	bool success = true;

	input.exceptions(std::ifstream::badbit);
	try {
		for (std::string line; getline(input, line); db.push_back(line));
	} catch (const std::iostream::failure& e) {
		std::cerr << "Error: Read failure." << std::endl;
		success = false;
	}
	input.clear();
	input.close();
	return success;
}

std::string get_delimiter(const std::string &first_line, std::string before,
                          std::string after) {
	if (first_line.find(before) == 0 &&
        first_line.find(after) != std::string::npos) {
        return first_line.substr(before.size(),
                                 first_line.size() - (before.size() + after.size()));
    } else
		return "";
}

void process_input_db(std::vector<std::string> &input_arr,
                      const std::vector<std::string> &db_arr) {
    BitcoinExchange be(db_arr,
                       get_delimiter(db_arr[0], "date", "exchange_rate"));
    for (std::vector<std::string>::iterator it = input_arr.begin() + 1;
         it != input_arr.end(); ++it) {
        if (!(*it).empty()) {
            try {
                std::cout << be.Querry(*it, get_delimiter(
                        input_arr[0], "date", "value")) << std::endl;
            } catch (const BitcoinExchange::BadInputException &e) {
                std::cerr << e.what() << *it << std::endl;
            } catch (const BitcoinExchange::InputFileCorruptedException &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

int main(int ac, char **av) {
    if (ac != 2) {
		std::cerr << "Error: wrong amount of arguments." << std::endl;
	} else {
		std::ifstream input, data;
		std::vector<std::string> input_arr, db_arr;

        if (open_files(input, data, av[1])) {
            bool input_read_success = read_from_file(input, input_arr);
            bool data_read_success = read_from_file(data, db_arr);
            if (input_read_success && data_read_success) {
                try {
                    process_input_db(input_arr, db_arr);
                    return 0;
                } catch (const BitcoinExchange::DatabaseFileCorruptedError &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
	}
	return 1;
}