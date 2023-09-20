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


class BitcoinExchange {
public:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange &);

    BitcoinExchange &operator=(const BitcoinExchange &);

    ~BitcoinExchange();

private:
};


#endif //EX00_BITCOINEXCHANGE_H