#include <unistd.h>
#include <iomanip>
#include "../includes/Game.h"
#include "utility.h"

void	Game::TurnStart(int &bet, int &prediction)
{
	system("clear");
	int from = user.dices.amount(),
		to = user.dices.range() * user.dices.amount();

	std::cout << "TURN #" << history_.size() + 1 << std::endl;
	std::cout << "Your current score: " << user.points << std::endl;
	std::cout << "Enter your prediction (" << from << "-" << to << "): ";
	std::cin >> prediction;

	if (prediction < from || prediction > to)
		return TurnStart(bet, prediction);

	std::cout << "Enter your bet for prediction (1-" << user.points << "): ";
	std::cin >> bet;

	if (bet < 0 || bet > user.points)
		return TurnStart(bet, prediction);
}

int		 Game::TurnEnd(int result, int bet)
{
	std::cout << "Now your score: " << user.points;
	std::cout << " (";
	if (result == 1) std::cout << cm("+" + std::to_string(bet * 3), green);
	if (result == -1) std::cout << cm("-" + std::to_string(bet), red);
	if (result == 0) std::cout << "0";
	std::cout << ")" << std::endl << std::endl;

	std::cout << "Want to quit? Type " << cm("EXIT", red) << "\n";
	if (!skip)
		std::cout << "Want to skip animation? Type " << cm("SKIP") << "\n";
	else
		std::cout << "Want to enable animation? Type " << cm("ENABLE") << "\n";
	std::cout << "Want to change color mode? Type " << cm("COLOR") << "\n";
	std::cout << "Want to continue? Type anything else\n";
	std::string command;
	std::cin >> command;
	system("clear");

	if (command == "EXIT")
		return 0;
	if (command == "COLOR")
		colorChange();
	if (command == "SKIP")
	{
		skip = true;
		std::cout << "Animation will be skipped\n";
		usleep(1000000);
	}
	if (command == "ENABLE")
	{
		skip = false;
		std::cout << "Animation will be enabled\n";
		usleep(1000000);
	}
	return 1;
}

int Game::turn()
{
	int bet, prediction,
		from = user.dices.amount(),
		to = user.dices.range() * user.dices.amount();

	TurnStart(bet, prediction);

	std::cout << "Your bet: " << bet << " point for prediction " << prediction << std::endl;

	history_.emplace_back(user.points, bet);
	std::cout << std::endl;
	int		result = user.dices.Match(prediction, skip);
	switch (result)
	{
		case 1:
			user.points += bet * 3;
			std::cout << cm("Congratulations, you win!\n", green);
			break;
		case -1:
			user.points -= bet;
			std::cout << cm("Oops, you loose!\n", red);
			break;
		default:
			std::cout << "You took bet back!\n";
	}

	if (user.points <= 0 || user.points >= user.win_condition)
	{
		bool win = user.points >= user.win_condition;
		std::string	clr = win ? green : red;
		std::cout << cm("You ", clr);
		std::cout << (win ? cm("win", clr) : cm("loss", clr));
		std::cout << cm(" the game with " + std::to_string(user.points) + "\n", clr);
		return 0;
	}

	return TurnEnd(result, bet);
}

std::string Game::cm(const std::string &str, const std::string& clr) const
{
	if (color)
		return clr + str + endc;
	else
		return str;
}

void Game::PrintHistory(std::ostream &out) const
{
	auto	dice_history = this->user.dices.history();
	out << std::setw(6) << "Turn" << std::setw(6) << "Score" << std::setw(6) << "Bet";
	out << std::setw(6) << "Pred" << " Result" << std::endl;
	for (size_t i = 0; i < history_.size(); i++)
	{
		out << std::setw(6) << i + 1 << std::setw(6) << history_[i].first;
		out << std::setw(6) << history_[i].second;
		out << std::setw(6) << dice_history[i].first << " ";
		out << std::setw(2) << Sum(dice_history[i].second) << ": ";

		for (size_t j = 0; j < dice_history[i].second.size() - 1; j++)
			out << dice_history[i].second[j] << "-";
		out << dice_history[i].second[dice_history[i].second.size() - 1] << " ";

		int result = user.dices.calculate(dice_history[i].first, Sum(dice_history[i].second));

		if (result == 1)
			out << cm(" win " + std::to_string(history_[i].second * 3) + " points\n", green);
		else if (result == -1)
			out << cm(" loss " + std::to_string(history_[i].second) + " points\n", red);
		else
			out << " nothing changed\n";
	}
}

void Game::colorChange() { color = !color; }
