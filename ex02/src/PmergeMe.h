/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    PmergeMe.h                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/29 19:24:14 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX02_PMERGEME_H
#define EX02_PMERGEME_H

#include <vector>
#include <list>

template <typename T1, typename T2>
struct ComPairAble : public std::pair<T1, T2> {
    ComPairAble() : std::pair<T1, T2>() {}

    ComPairAble(T1 first, T2 second) : std::pair<T1, T2>(
            first < second ? first : second,
            second < first ?  first : second) {}

    bool operator<(const ComPairAble &rhs) const {
        return this->second < rhs.second;
    }

    bool operator>(const ComPairAble &rhs) const {
        return this->second > rhs.second;
    }

    bool operator==(const ComPairAble &rhs) const {
        return this->second == rhs.second;
    }
};

int FJSort(std::vector<int> &);
int FJSort(std::list<int> &);
int NaiveSort(std::list<int> &);

#endif //EX02_PMERGEME_H
