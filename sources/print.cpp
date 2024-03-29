#include <iomanip>
#include "../includes/Dices.h"
#include "../includes/utility.h"

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

void Dices::PrintInfo(int prediction, int sum, bool color) const
{
	int	istrue = calculate(prediction, sum);
	std::cout << "Needed to be ";
	if (istrue == -1) 	std::cout << red;
	else				std::cout << green;
	if (in && prediction <= separator)
	{
		std::cout << "less or equal to ";
		istrue = sum <= separator;
	}
	else if (!in && prediction < separator)
	{
		std::cout << "less then ";
		istrue = sum < separator;
	}
	else
	{
		std::cout << "more then ";
		istrue = sum > separator;
	}
	std::cout << endc;
	std::cout << separator << " to take your bet back" << std::endl;
	if (!color)
		std::cout << "CURRENT SUM NOW = " << sum << std::endl;
	else
	{
		std::cout << "CURRENT SUM NOW = ";
		if (prediction >= sum)
			std::cout << green << sum << endc << std::endl;
		else
			std::cout << red << sum << endc << std::endl;
	}
	std::cout << "YOUR PREDICTION = " << prediction << std::endl;
}

void 	Dices::PrintDice(std::vector<int> const &results) const
{
	if (this->range() < 10)
	{
		for (int i = 1; i <= 5; i++)
		{
			for (auto item : results)
				PrintLine(std::cout, item, i);
			std::cout << "\n";
		}
		std::cout << std::endl;
	}
	else
	{
		for (auto item : results)
			std::cout << "[" << std::setw(2) << item << "] ";
		std::cout << std::endl;
	}
}