#pragma once

#define red 	"\033[1;31m"
#define green 	"\033[1;32m"
#define blue 	"\033[1;34m"
#define black 	"\033[1;30m"
#define endc 	"\033[0m"
#define tab 	setw(6)
#define wait 	usleep(1000000)
#define clear	system("clear")
#define max_win 10000

int		Sum(std::vector<int> const &result, size_t j = 0);
bool 	countSeparator(int number, int range, int &answer);

