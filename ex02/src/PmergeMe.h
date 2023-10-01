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

struct PmergeMe {
    static void FJSort(std::vector<int> &arr);
    static void FJSort(std::list<int> &lst);
};


#endif //EX02_PMERGEME_H