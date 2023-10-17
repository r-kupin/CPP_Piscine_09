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

static const int jacobsthal_diff[] = {
		2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
		2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
		1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
		178956970, 357913942, 715827882, 1431655766};

//static const int jacobsthal[] = {1, 3, 5, 11, 21, 43};

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

void make_s_pend(std::vector<int> &s, std::vector<int> &pend,
		std::vector<std::pair<int, int> > &pairs) {
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		s[i + 1] = pairs[i].second;
		pend[i + 1] = pairs[i].first;
	}
}

int jacobstahl_get(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int prev1 = 1;
	int prev2 = 0;
	int current = 0;

	for (int i = 2; i <= n; ++i) {
		current = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = current;
	}

	return current;
}

std::vector<int> build_js_sequence(std::vector<int> &pend, int js_i) {
	std::vector<int> end;

	for (; jacobstahl_get(js_i) < (int)pend.size(); js_i += 1) {
		end.push_back(jacobstahl_get(js_i));
	}
	return end;
}

bool gotta_use_jacobstahl(int amount_of_non_js_numbers_used_since_last_one) {
	static int index_of_last_js_number_used;
	if (index_of_last_js_number_used == 0)
		index_of_last_js_number_used = 1;
	if (amount_of_non_js_numbers_used_since_last_one == jacobsthal_diff[index_of_last_js_number_used] - 1) {
		index_of_last_js_number_used++;
		return true;
	}
	return false;
}

void PmergeMe::FJSort(std::vector<int> &arr) {
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

	/**
	 * Step 3:
	 * Consider that the highest values form a sorted list that we will
	 * call the S while the rest of the elements will be known as pend elements.
	 * Tag the elements of the S with the names A1,A2,A3,...,An/2 then
	 * tag the pend elements with the names B1,B2,B3,...,Bn/2.
	 * For every n, we have the relation Bn ≤ An.
 	 */
    std::vector<int> s(pairs.size() + 1);
    std::vector<int> pend(pairs.size() + 1);
	make_s_pend(s, pend, pairs);

	/**
	 * Step 4:
	 * Insert the pend elements into the main chain. We know that the
	 * first pend element B1 is lesser than A1;
	 * we consider it to be part of the main chain which then becomes {B1,A1,A2,A3,...,An/2}
 	 */
    s.insert( s.begin() + 1, pend[1]);
//	pend.erase(pend.begin());

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
	 * as follows: B1,B3,B2,B5,B4,B11,B10,B9,B8,B7,B6,...
 	 */
//	iterate pend
	int pend_i = 1;
//	non-jacobstahl picks amount
	int non_js = 1;

//	keep track of pend indexes that we already inserted inside the s
    std::vector<int> index_sequence(1, 1);
//	build the valid jacobsthal sequence regarding the remain size of pend.
//	3 - first relevant jacobstahl number to use. Sequence is defined as 0 1 1 3 5 11 ...
//	{0, 1} first elements, here are just to define the sequence
//	{1} first element, but we already used it in a previous step
//	{3} here we go
    std::vector<int> jacob_insertion_sequence = build_js_sequence(pend, 3);
//	value from pend to insert
    int item;
//	index in s where to insert
    int insertionPoint;
    for (; pend_i < (int)pend.size(); pend_i++) {
        if (!jacob_insertion_sequence.empty() && gotta_use_jacobstahl(non_js)) {
        	non_js = 0;
			// we can use jacobstahl number, so let's put it in index_sequence to mark it's use
            index_sequence.push_back(jacob_insertion_sequence[0]);
			// take the value of the pend element by the index from jacobstahl sequence.
			// Substract 1, because C++ is 0-indexed.
            item = pend[jacob_insertion_sequence[0]];
			// Remove used jacobstahl number from the list of available numbers
            jacob_insertion_sequence.erase(jacob_insertion_sequence.begin());
			// mark that element was inserted using jacobstahl number
        } else {
			// we can't use jacobstahl number, because one was already used, or no available left.
			// check if current index was already used. If yes - pick next one.
            if (std::find(index_sequence.begin(), index_sequence.end(), pend_i)
                != index_sequence.end()) {
                pend_i++;
            }
            // pend_inexes go in line with jacobstahl numbers, so they are not 0-indexed
            item = pend[pend_i];
            index_sequence.push_back(pend_i);
        }
		// find appropriate index where to insert the item
        insertionPoint = std::lower_bound(s.begin() + 1, s.end(), item) - s.begin();
		// insert
        s.insert(s.begin() + insertionPoint, item);
    }
	// insert a straggler if it was noted
    if (straggler != -1) {
        insertionPoint = std::lower_bound(s.begin(), s.end(), straggler) -
                         s.begin();
        s.insert(s.begin() + insertionPoint, straggler);
    }
    s.erase(s.begin());
    arr = s;
    std::cout << std::endl;
}


void PmergeMe::FJSortInPlace(std::vector<int> &arr) {
	int straggler = -1;
	if (arr.size() % 2 == 1)
		straggler = *(arr.end() - 1);


}

void PmergeMe::FJSort(std::list<int> &lst) {
    (void)lst;
}
