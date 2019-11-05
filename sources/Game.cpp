#include <unistd.h>
#include <iomanip>
#include "../includes/Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::to_string;

void	Game::TurnStart(int &bet, int &prediction)
{
	system("clear");
	int from = user.dices.amount(),
		to = user.dices.range() * user.dices.amount();

	cout << "TURN #" << history_.size() + 1 << endl;
	cout << "Your current score: " << user.points << endl;
	cout << "Enter your prediction (" << from << "-" << to << "): ";
	cin >> prediction;

	if (prediction < from || prediction > to)
		return TurnStart(bet, prediction);

	cout << "Well, chance of match is " << std::setprecision(4) << std::fixed << user.dices[prediction] * 100 << "%\n";
	cout << "Enter your bet for prediction (1-" << user.points << "): ";
	cin >> bet;

	if (bet < 0 || bet > user.points)
		return TurnStart(bet, prediction);
}

int		 Game::TurnEnd(int result, int bet)
{
	cout << "Now your score: " << user.points;
	cout << " (";
	if (result == 1) cout << cm("+" + to_string(bet * 3), green);
	if (result == -1) cout << cm("-" + to_string(bet), red);
	if (result == 0) cout << "0";
	cout << ")" << endl << endl;

	cout << "Want to quit? Type " << cm("EXIT", red) << "\n";
	if (!skip)
		cout << "Want to skip animation? Type " << cm("SKIP") << "\n";
	else
		cout << "Want to enable animation? Type " << cm("ENABLE") << "\n";
	cout << "Want to change color mode? Type " << cm("COLOR") << "\n";
	cout << "Want to continue? Type anything else\n";
	string command;
	cin >> command;
	system("clear");

	if (command == "EXIT")
		return 0;
	if (command == "COLOR")
		color = !color;
	if (command == "SKIP")
	{
		skip = true;
		cout << "Animation will be skipped\n";
	}
	if (command == "ENABLE")
	{
		skip = false;
		cout << "Animation will be enabled\n";
	}
	wait;
	return 1;
}

int Game::turn()
{
	int bet, prediction,
		from = user.dices.amount(),
		to = user.dices.range() * user.dices.amount();

	TurnStart(bet, prediction);

	cout << "Your bet: " << bet << " point for prediction " << prediction << endl;
	wait;
	system("clear");

	history_.emplace_back(user.points, bet);
	cout << endl;
	int		result = user.dices.Match(prediction, skip, color);
	switch (result)
	{
		case 1:
			user.points += bet * 3;
			cout << cm("Congratulations, you win!\n", green);
			break;
		case -1:
			user.points -= bet;
			cout << cm("Oops, you loose!\n", red);
			break;
		default:
			cout << "You took bet back!\n";
	}

	if (user.points <= 0 || user.points >= user.win_condition)
	{
		bool win = user.points >= user.win_condition;
		string	clr = win ? green : red;
		cout << cm("You ", clr);
		cout << (win ? cm("win", clr) : cm("loss", clr));
		cout << cm(" the game with " + to_string(user.points) + "\n", clr);
		return 0;
	}

	return TurnEnd(result, bet);
}

string Game::cm(const string &str, const string& clr) const
{
	return (color) ? clr + str + endc : str;
}

void Game::PrintHistory(std::ostream &out) const
{
	auto	dice_history = this->user.dices.history();
	out << tab << "Turn" << tab << "Score" << tab << "Bet";
	out << tab << "Pred" << " Result" << endl;
	for (size_t i = 0; i < history_.size(); i++)
	{
		out << tab << i + 1 << tab << history_[i].first;
		out << tab << history_[i].second;
		out << tab << dice_history[i].first << " ";
		out << setw(2) << Sum(dice_history[i].second) << ": ";

		for (size_t j = 0; j < dice_history[i].second.size() - 1; j++)
			out << dice_history[i].second[j] << "-";
		out << dice_history[i].second[dice_history[i].second.size() - 1] << " ";

		int result = user.dices.calculate(dice_history[i].first, Sum(dice_history[i].second));

		if (result == 1)
			out << cm(" win " + to_string(history_[i].second * 3) + " points\n", green);
		else if (result == -1)
			out << cm(" loss " + to_string(history_[i].second) + " points\n", red);
		else
			out << " nothing changed\n";
	}
}
