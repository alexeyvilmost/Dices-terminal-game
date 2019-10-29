//
// Created by alexeyvilmost on 28.10.2019.
//

#ifndef KEK_GAME_H
#define KEK_GAME_H

#include <utility>

#include "../sources/User.cpp"
#include "../sources/utility.h"

class Game
{
public:
	using turn_data = std::pair<int, int>; // {score, bet}
	explicit 	Game(User usr, bool skip = false, bool color = true)
	: user(std::move(usr)), skip(skip), color(color) {};
	int			turn();
	int			TurnEnd(int result, int bet);
	void		TurnStart(int &bet, int &prediction);
	void 		PrintHistory(std::ostream& out) const;
	std::string	cm(const std::string &fill, const std::string& color = blue) const;
	bool		color;

private:
	void 					colorChange();
	User 					user;
	bool					skip;
	std::vector<turn_data>	history_;
};


#endif //KEK_GAME_H
