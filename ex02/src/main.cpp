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
#include <vector>
#include <list>

int main(int ac, char **av) {
    if (ac < 3) {
        std::cerr << "Error: not enough elements in the list." << std::endl;
        return 1;
    }

    std::vector<int> vec(ac - 1);
    std::list<int> list;

    for (int i = 1; i < ac; ++i) {
        std::string str(av[i]);
        if(str.find_first_not_of("0123456789") != std::string::npos) {
            vec.[i - 1] = std::atoi(str);
            list.push_back(std::atoi(str));
        }
    }

    return 0;
}
