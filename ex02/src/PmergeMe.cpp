/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    PmergeMe.cpp                                       :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/09/29 19:24:14 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "PmergeMe.h"

/**
 * The Jacobsthal sequence and the number of comparisons needed for binary search are related in the sense that the Jacobsthal sequence can help you determine the number of comparisons needed for binary search in a worst-case scenario.
 * The Jacobsthal sequence is defined as follows:
 * 	J(0) = 0
 * 	J(1) = 1
 * 	J(n) = J(n-1) + 2*J(n-2) for n > 1
 * 	It's similar to the Fibonacci sequence but uses different recurrence relations. The Jacobsthal sequence is related to binary search because it represents the number of comparisons required to find an element not present in a sorted array using binary search.
 * 	In a sorted array with 2^n elements, binary search typically requires n comparisons to find an element not present.
 * 	If you represent this as a sequence, it corresponds to the Jacobsthal sequence with J(0) = 0 and J(1) = 1. So, J(n) represents the number of comparisons needed for binary search in an array of size 2^n when searching for an element not present.
 * 	For example:
 * 	J(2) = J(1) + 2J(0) = 1 + 2*0 = 1 (for an array of size 4)
 * 	J(3) = J(2) + 2J(1) = 1 + 2*1 = 3 (for an array of size 8)
 * 	In summary, the Jacobsthal sequence can be used to determine the number of comparisons needed for binary search in a sorted array when searching for an element not present, specifically in cases where the array size is a power of 2.
 */


std::vector<int>::iterator my_bin_search(std::vector<int>::iterator begin, std::vector<int>::iterator end, int target) {
	std::vector<int>::iterator median;

	for (median = begin + (end - begin) / 2;
			*median != target && begin != end;
			median = begin + (end - begin) / 2) {
		if (*median < target) {
			begin = median;
		} else if (*median > target) {
			end = median;
		}
	}
	return median;
}


void insert_remaining(std::vector<int> &s,
					  std::vector<std::pair<int, int> >::iterator from,
					  std::vector<std::pair<int, int> >::iterator to) {
	for(; from >= to; --from) {
		int insertion_point = std::lower_bound(s.begin(), s.end(), (*from).first) - s.begin();
		s.insert(s.begin() + insertion_point, (*from).first);
	}
}

bool	all_non_js_indeces_used_between_last_and_prev_js(int current_js_index_used,
													  int iterations_after_last_js,
													  const std::vector<int> &jacobsthal) {
	return iterations_after_last_js ==
		   (jacobsthal[current_js_index_used] - jacobsthal[current_js_index_used - 1] - 1);
}

bool first_iteration(int current_js_index_used) {return current_js_index_used == 0;}

void	form_pairs(std::vector<int> &arr,
		std::vector<std::pair<int, int> > &pairs) {
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		if (arr[i * 2] > arr[i * 2 + 1]) {
			pairs[i].first = arr[i * 2 + 1];
			pairs[i].second = arr[i * 2];
		} else {
			pairs[i].first = arr[i * 2];
			pairs[i].second = arr[i * 2 + 1];
		}
	}
}

void	sort_pairs(std::vector<std::pair<int, int> > &pairs) {
	for (std::size_t i = 1; i < pairs.size(); ++i) {
		std::pair<int, int> x = pairs[i];
		int j = (int)i - 1;
		for (; j >= 0 && pairs[j].second > x.second ; j--) {
			pairs[j + 1] = pairs[j];
		}
		pairs[j + 1] = x;
	}
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin();
		it != pairs.end(); ++it) {
	}
}

std::vector<int> jacobstahl_get(int n) {
	std::vector<int> sequence = {1, 3};
	for (int i = 1; ; ++i) {
		sequence.push_back(sequence[i] + sequence[i - 1] * 2);
		if (sequence[i] > n)
			break;
	}
	return sequence;
}

void FJSortInPlace(std::vector<int> &arr) {
	/**
	 * Step 1:
	 * handle the straggler element - memoize the last element if number of
	 * elements is odd
	 */
	int straggler = -1;
	if (arr.size() % 2 == 1)
		straggler = *(arr.end() - 1);

	/**
	 * Step 2:
	 * Split the collection in n/2 pairs of 2 elements and order these
	 * elements pairwise. Then sort the pairs of elements by their highest value
	 */
	std::vector<std::pair<int, int> > pairs(arr.size() / 2);
	form_pairs(arr, pairs);
	sort_pairs(pairs);

	const std::vector<int> jacobstahl_sequence = jacobstahl_get(pairs.size());
	/**
	 * Step 3:
	 * Consider that the highest values form a sorted list that we will
	 * call the S while the rest of the elements will be known as pend elements.
	 * Tag the elements of the S with the names A1,A2,A3,...,An/2 then
	 * tag the pend elements with the names B1,B2,B3,...,Bn/2.
	 * For every n, we have the relation Bn ≤ An.
	 * Insert the pend elements into the main chain. We know that the
	 * first pend element B1 is lesser than A1;
	 * we consider it to be part of the main chain which then becomes {B1,A1,A2,A3,...,An/2}
 	 */
	std::vector<int> s(pairs.size() + 1);

	s[0] = pairs[0].first;
	for (std::size_t i = 1; i <= pairs.size(); ++i)
		s[i] = pairs[i - 1].second;

	for (auto it = s.begin(); it != s.end(); ++it) {
		std::cout << std::setw(2) << *it << " ";
	}
	std::cout << std::endl;

	for (auto it = pairs.begin(); it != pairs.end(); ++it) {
		std::cout << std::setw(2) << (*it).second << " ";
	}
	std::cout << std::endl;

	for (auto it = pairs.begin(); it != pairs.end(); ++it) {
		std::cout << std::setw(2) << (*it).first << " ";
	}
	std::cout << std::endl;

	/**
	 * Step 5:
	 * insert the other pend elements into the main chain in a way that ensures that
	 * the size of the insertion area is a power of 2 minus 1 as often as possible.
	 * Basically, we will insert B3 in {B1,A1,A2} (we know that it is less than A3),
	 * then we will insert B2 into {B1,A1,B3} no matter where B3 was inserted.
	 * Note that during these insertions, the size of the insertion area is always at most 3.
	 * The value of the next pend element bk to insert into the main chain
	 * while minimizing the number of comparisons actually corresponds to
	 * the next Jacobsthal number.
	 * We inserted the element 3 first, so the next will be 5 then 11 then 21, etc...
	 * To sum up, the insertion order of the first pend elements into the main chain is
	 * as follows: <B1>,<B3>,B2,<B5>,B4,<B11>,B10,B9,B8,B7,B6,<B21>,B20 ...
 	 */
	int current_js_index_used = 0, iterations_after_last_js = 0;

	std::cout << 1 << " ";

	for (size_t pend_i = 0; ;) {
		std::pair<int, int> item;
		if (first_iteration(current_js_index_used) ||
			all_non_js_indeces_used_between_last_and_prev_js(
					current_js_index_used,iterations_after_last_js, jacobstahl_sequence)) {
			int index_in_pend_to_take = jacobstahl_sequence[++current_js_index_used] -1;
			if (index_in_pend_to_take >= pairs.size()) {
				insert_remaining(s, pairs.end() - 1, pairs.begin() + jacobstahl_sequence[current_js_index_used - 1]);
				break;
			}
			item = pairs[index_in_pend_to_take];
			std::cout << index_in_pend_to_take + 1 << " ";
			pend_i = jacobstahl_sequence[current_js_index_used] - 2;
			iterations_after_last_js = 0;
		} else {
			item = pairs[pend_i];
			std::cout << pend_i + 1 << " ";
			++iterations_after_last_js;
			--pend_i;
		}
		std::vector<int>::iterator insertion_point = my_bin_search(s.begin(), s.end(), item.first);
		s.insert(insertion_point, item.first);
	}
	std::cout << std::endl;
}