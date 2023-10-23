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

template <typename Container>
struct Profiler {
	typedef int (*PTF)(Container&);

	static Profiler Profile(PTF sort, Container& container) {
		int comparations;
		
		clock_t start_time = clock();
		comparations = sort(container);
		clock_t end_time = clock();
		return Profiler(
				(double)(end_time - start_time) / CLOCKS_PER_SEC,
				comparations);
	}

	double	time_;
	int		comparisons_;
	
private:
	Profiler(double time, int comparations) 
	: time_(time), comparisons_(comparations) {}
};

template <typename Container, typename Iterator>
void sort_report(Container &cnt, const std::string &name) {
	std::cout << "Before:\t";
	for (Iterator it = cnt.begin(); it != cnt.end(); ++it) {
		std::cout << std::setw(2) << *it << " ";
	}
	std::cout << " size " << cnt.size() << std::endl;

	const Profiler<Container> &vec_p =
			Profiler<Container>::Profile(&FJSort, cnt);

	std::cout << "After:\t";
	for (Iterator it = cnt.begin(); it != cnt.end(); ++it) {
		std::cout << std::setw(2) << *it << " ";
	}
	std::cout << " size " << cnt.size() << std::endl;
	std::cout << std::endl;

	std::cout << "Time to process a range of " << cnt.size() << " elements " <<
			  name << ":\t" << std::fixed << vec_p.time_ << " us" <<
			  " and " << vec_p.comparisons_ << " comparisons made\n" <<
			  std::endl;
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
	sort_report<std::vector<int>, std::vector<int>::iterator>(vec,
															  "std::vector");
	sort_report<std::list<int>, std::list<int>::iterator>(list,
														  "std::list");
    return 0;
}
