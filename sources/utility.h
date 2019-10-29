//
// Created by alexeyvilmost on 29.10.2019.
//

#ifndef KEK_UTILITY_H
#define KEK_UTILITY_H

#define red "\033[1;31m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define black "\033[1;30m"
#define endc "\033[0m"

int		Sum(std::vector<int> const &result, size_t j = 0);
bool 	countSeparator(int number, int range, int &answer);

#endif //KEK_UTILITY_H
