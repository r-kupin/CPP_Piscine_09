/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    main.cpp                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/27 21:51:41 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "PmergeMe.h"

// Cant use template with typedef, and alias declarators are c++11 :(
//template <typename Container>
//using PTF = void (*)(Container&);
//
//template <typename Container>
//double profile(PTF<Container> func, Container& container) { ... }

template <typename Container>
double profile(void (*sort)(Container&), Container& container) {
    clock_t start_time = clock();
    sort(container);
    clock_t end_time = clock();
    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void sort_n_compare(std::vector<int> &vec, std::list<int> &list) {
    std::cout << "Before:\t";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    double arr_time = profile(&PmergeMe::FJSort, vec);
	double in_place_time = profile(&PmergeMe::FJSortInPlace, vec);
	double list_time = profile(&PmergeMe::FJSort, list);

    std::cout << "After:\t";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vec.size() << " elements " <<
        "std::vector<int>\t: " << std::fixed << arr_time << " us" << std::endl;
    std::cout << "Time to process a range of " << vec.size() << " elements in place " <<
        "std::vector<int>\t: " << std::fixed << in_place_time << " us" << std::endl;
    std::cout << "Time to process a range of " << list.size() << " elements " <<
        "std::list<int>\t: " << std::fixed << list_time << " us" << std::endl;
}

int     main(int ac, char **av) {
    if (ac < 3) {
        std::cerr << "Error: not enough elements in the list." << std::endl;
        return 1;
    }
    std::vector<int> vec(ac - 1);
    std::list<int> list;
    for (int i = 1; i < ac; ++i) {
        std::string str(av[i]);
        if (str.find_first_not_of("0123456789") == std::string::npos) {
            vec[i - 1] = atoi(str.c_str());
            list.push_back(atoi(str.c_str()));
        } else {
            std::cerr << "Error: bad input." << std::endl;
            return 1;
        }
    }
    sort_n_compare(vec, list);
    return 0;
}
