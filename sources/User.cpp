#include <utility>

#include "../includes/Dices.h"



struct User
{
	int			points;
	size_t		win_condition;
	Dices		dices;
	std::string	name;

	explicit User(
		size_t start = 100,
		size_t win = 500,
		std::string username = "default",
		Dices cubes = Dices(6, 2)) :

		points(start),
		win_condition(win),
		name(std::move(username)),
		dices(std::move(cubes)) {}
};
