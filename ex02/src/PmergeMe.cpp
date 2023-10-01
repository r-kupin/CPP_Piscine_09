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
#include "PmergeMe.h"

int jacobstahl(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobstahl(n - 1) + 2 * jacobstahl(n - 2);
}

std::vector<int> build_js_sequence(std::vector<int> &arr) {
    std::vector<int> end;
    int j_s_index = 3;

    while (jacobstahl(j_s_index) < (int)arr.size() - 1) {
        end.push_back(jacobstahl(j_s_index));
        j_s_index += 1;
    }
    return end;
}

void PmergeMe::FJSort(std::vector<int> &arr) {
    int straggler = -1;
    if (arr.size() % 2 == 1)
        straggler = *(arr.end() - 1);

    std::vector<std::pair<int, int> > pairs(arr.size() / 2);

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (arr[i * 2] > arr[i * 2 + 1]) {
            pairs[i].first = arr[i * 2 + 1];
            pairs[i].second = arr[i * 2];
        } else {
            pairs[i].first = arr[i * 2];
            pairs[i].second = arr[i * 2 + 1];
        }
    }

    for (std::size_t i = 1; i < pairs.size(); ++i) {
        std::pair<int, int> x = pairs[i];
        int j = (int)i - 1;
        for (; j >= 0 && pairs[j].second > x.second ; j--) {
            pairs[j + 1] = pairs[j];
        }
        pairs[j + 1] = x;
    }

    std::vector<int> s(pairs.size());
    std::vector<int> pend(pairs.size());
    for (std::size_t i = 0; i < pairs.size(); ++i) {
        s[i] = pairs[i].second;
        pend[i] = pairs[i].first;
    }

    s.insert( s.begin(), pend[0]);
    pend.erase(pend.begin());

    std::vector<int> index_sequence(1);
    index_sequence[0] = 1;
    std::string last = "default";

    std::vector<int> jacob_insertion_sequence = build_js_sequence(pend);
    int item, insertionPoint;

    for (int it = 0; it <= (int)pend.size();) {
        if (!index_sequence.empty() && last != "jacob") {
            index_sequence.push_back(jacob_insertion_sequence[0]);
            item = pend[jacob_insertion_sequence[0] - 1];
            jacob_insertion_sequence.erase(jacob_insertion_sequence.begin());
            last = "jacob";
        } else {
            if (std::find(index_sequence.begin(), index_sequence.end(), it)
                != index_sequence.end()) {
                it++;
            }
            item = pend[it - 1];
            index_sequence.push_back(it);
            last = "not-jacob";
        }
        insertionPoint = std::lower_bound(s.begin(), s.end(), item) -
                                                s.begin();
        s.insert(s.begin() + insertionPoint, item);
        it++;
    }

    if (straggler != -1) {
        insertionPoint = std::lower_bound(s.begin(), s.end(), straggler) -
                         s.begin();
        s.insert(s.begin() + insertionPoint, straggler);
    }
}

void PmergeMe::FJSort(std::list<int> &lst) {
    (void)lst;
}
