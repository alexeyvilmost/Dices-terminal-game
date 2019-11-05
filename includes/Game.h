#pragma once

#include <utility>

#include "../sources/User.cpp"
#include "utility.h"

class Game
{
public:
	using 					turn_data = std::pair<int, int>; // {score, bet}

	explicit 				Game(User usr, bool skip = false, bool color = true) //Constructor from user
	: user(std::move(usr)), skip(skip), color(color) {};
	int						turn(); //Main interface, handling turn
	void 					PrintHistory(std::ostream& out) const; //Final print
	std::string				cm(const std::string &fill, const std::string& color = blue) const; //Checks if color enable
	bool					color;

private:
	int						TurnEnd(int result, int bet);
	void					TurnStart(int &bet, int &prediction);

	User 					user;
	bool					skip;
	std::vector<turn_data>	history_;
};
