#include <iomanip>
#include "../includes/Dices.h"
#include "utility.h"

char		dot(bool condition) { return (condition) ? '0' : ' '; }

static std::string h = "   ";

static void	PrintLine(std::ostream& out, int result, int line)
{
	switch (line)
	{
		case 1:
			out << " ------- " << h; break;
		case 2:
			out << "| " << dot(result > 3) << " " << dot(result >= 6) << " "
			<< dot(result != 1) << " |" << h; break;
		case 3:
			out << "| " << dot(result >= 8) << " " << dot(result % 2 == 1) << " "
			<< dot (result >= 8) << " |" <<  h; break;
		case 4:
			out << "| " << dot(result != 1) << " " << dot(result >= 6) << " "
			<< dot(result > 3) << " |" << h; break;
		default:
			out << " ------- " << h; break;
	}
}

void Dices::PrintInfo(int prediction, int sum) const
{
	std::cout << "Needed to be ";
	if (in && prediction <= separator)
		std::cout << "less or equal to ";
	else if (!in && prediction < separator)
		std::cout << "less then ";
	else
		std::cout << "more then ";
	std::cout << separator << " to take your bet back" << std::endl;
	std::cout << "CURRENT SUM NOW = " << sum << std::endl;
	std::cout << "YOUR PREDICTION = " << prediction << std::endl;
}

void 	Dices::PrintDice(std::vector<int> const &results) const
{
	std::cout << black;
	if (this->range() < 10)
		for (int i = 1; i <= 5; i++)
		{
			for (auto item : results)
				PrintLine(std::cout, item, i);
			std::cout << std::endl;
		}
	else
	{
		for (auto item : results)
			std::cout << "[" << std::setw(2) << item << "] ";
		std::cout << std::endl;
	}
	std::cout << endc;
}