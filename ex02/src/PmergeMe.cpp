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

#include <algorithm>
#include <iostream>
#include <iterator>
#include "PmergeMe.h"

int comparations = 0;

/**
 *	Generates array of Jacobstahl numbers by the formula:
 *	J(0) = 1
 *	J(1) = 3
 *	J(n) = J(n-1) + 2*J(n-2) for n > 1
 * @param n - biggest Jacobstahl number that we will need
 */
std::vector<int> jacobstahl_get(int n) {
	std::vector<int> sequence(2);
    sequence[0] = 1;
    sequence[1] = 3;
	for (int i = 1; ; ++i) {
		sequence.push_back(sequence[i] + sequence[i - 1] * 2);
		if (sequence[i] > n)
			break;
	}
	return sequence;
}

/**
 * Simple iterative function performing binary search in the sorted range
 * between 2 iterators, and counting comparisons
 * @tparam T target - value we are looking for
 * @param begin - beginning of search zone, included
 * @param end - end of search zone, included
 * @return iterator of the found element, or to the closest bigger one if
 * element isn't present
 */
template <typename Iterator, typename T>
Iterator bin_search(Iterator begin, Iterator end, const T& target) {
    Iterator result = end;

    while (begin != end) {
        Iterator mid = begin;
        std::advance(mid, std::distance(begin, end) / 2);

        if (*mid < target) {
            comparations++;
            std::advance(begin, 1);
        } else if (*mid > target) {
            comparations += 2;
            result = mid;
            end = mid;
        } else {
            comparations += 2;
            return mid;
        }
    }
    return result;
}
/**
 * Function used to insert the remaining elements when all Jacobstahl numbers
 * are already used
 * @param sink - the collection where to insert
 * @param source_from - iterator to first element to insert
 * @param source_up_to - iterator to last element to insert
 */
template <typename Iterator, typename Container>
void insert_remaining(Container &sink, Iterator source_from,
					  Iterator source_up_to) {
	for(; source_from >= source_up_to; --source_from) {
		sink.insert(
				bin_search(sink.begin(),
						   sink.end() - 1,
						   (*source_from).first),
											(*source_from).first);
	}
}

/**
 * Checks whether we need to jump to the next jacobstahl number or not
 * If we already performed all iterations, that form up a distance between
 * the last jacobstahl number used, and one we used before - we need to grab
 * the nex one from jacobsthal sequence
 */
bool	all_non_js_indeces_between_last_and_prev_js_used(
		int current_js_index_used, int iterations_after_last_js,
		const std::vector<int> &jacobsthal) {
	return iterations_after_last_js ==
			(jacobsthal[current_js_index_used] -
			jacobsthal[current_js_index_used - 1] - 1);
}

/**
 * The first iteration is a bit special, because we need to use 2 jacobsthal
 * numbers in row - 1 and 3.
 */
bool first_iteration(int current_js_index_used) {
	return current_js_index_used == 0;
}

/**
 * Function creates list of pairs, consisting of even and odd elements from
 * input countainer arranging elements in this pairs in a way that first
 * element is always smaller or equal to second
 */
template<typename Iterator, typename PairContainer>
void form_pairs(Iterator begin, Iterator end, PairContainer &pairs) {
	Iterator p_it = begin;
    Iterator s_it = ++p_it;
	for (p_it = begin; s_it != end && p_it != end; std::advance(p_it, 2),
                                                    std::advance(s_it, 2)) {
		ComPairAble<int, int> p(*p_it, *s_it);
		pairs.insert(bin_search(pairs.begin(), pairs.end(), p), p);
        comparations++;
    }
}

void FJSort(std::vector<int> &arr) {
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
	std::vector<ComPairAble<int, int> > pairs;
    form_pairs(arr.begin(), arr.end(), pairs);

	const std::vector<int> jacobstahl_sequence =
            jacobstahl_get(static_cast<int>(pairs.size()));
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

	/**
	 * Step 4:
	 * insert the other pend elements into the main chain in a way that ensures that
	 * the size of the insertion area is a jacobstahl number power of 2 minus 1.
	 * Basically, we will insert B3 in {B1,A1,A2} (we know that it is less
	 * than A3),
	 * then we will insert B2 into {B1,A1,B3} no matter where B3 was inserted.
	 * During these insertions, the size of the insertion area is always at
	 * most 3.
	 * The value of the next pend element Bk to insert into the main chain
	 * while minimizing the number of comparisons actually corresponds to
	 * the next Jacobsthal number, and insertion area will be it's power of 2.
	 * We inserted the element 3 first, so the next will be 5 then 11 then 21, etc...
	 * To sum up, the insertion order of the first pend elements into the main chain is
	 * as follows: <B1>,<B3>,B2,<B5>,B4,<B11>,B10,B9,B8,B7,B6,<B21>,B20 ...
 	 */
	int current_js_index_used = 0, iterations_after_last_js = 0;

	for (size_t pend_i = 0; ;) {
		std::pair<int, int> item;
		if (first_iteration(current_js_index_used) ||
				all_non_js_indeces_between_last_and_prev_js_used(
						current_js_index_used, iterations_after_last_js,
						jacobstahl_sequence)) {
			int index_in_pend_to_take = jacobstahl_sequence[++current_js_index_used] -1;
			if (index_in_pend_to_take >= static_cast<int>(pairs.size())) {
				insert_remaining(s, pairs.end() - 1,
						pairs.begin() + jacobstahl_sequence[current_js_index_used - 1]);
				break;
			}
			item = pairs[index_in_pend_to_take];
			pend_i = jacobstahl_sequence[current_js_index_used] - 2;
			iterations_after_last_js = 0;
		} else {
			item = pairs[pend_i];
			++iterations_after_last_js;
			--pend_i;
		}
		v_iter insertion_point = bin_search(s.begin(),
				s.begin() + (2 << current_js_index_used) - 1, item.first);
		s.insert(insertion_point, item.first);
	}
	if (straggler != -1) {
		v_iter insertion_point = bin_search(s.begin(), s.end(), straggler);
		s.insert(insertion_point, straggler);
	}
	arr = s;
	std::cout << "(" << comparations << ")" << " comparisons performed" << std::endl;
}
