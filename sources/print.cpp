#include <iomanip>
#include "../includes/Dices.h"
#include "../includes/utility.h"

using std::cout;

static std::string h = "   ";

char		dot(bool condition) { return (condition) ? '0' : ' '; }

static void	PrintLine(std::ostream& out, int result, int line)
{
	switch (line)
	{
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
	{
		cout << "Needed to be ";

		if (color)
			cout << ((calculate(prediction, sum) == -1) ? red : green);
		if (in && prediction <= separator)
			cout << "less or equal to ";
		else if (!in && prediction < separator)
			cout << "less then ";
		else if (prediction > separator)
			cout << "more then ";
		else
			cout << "equal to ";
		if (color) cout << endc;
		cout << separator << " to take your bet back" << std::endl;
	}
	if (!color)
		cout << "CURRENT SUM NOW = " << sum << std::endl;
	else
	{
		cout << "CURRENT SUM NOW = ";
		if (prediction >= sum)
			cout << green << sum << endc << std::endl;
		else
			cout << red << sum << endc << std::endl;
	}
	cout << "YOUR PREDICTION = " << prediction << std::endl;
}

void 	Dices::PrintDice(std::vector<int> const &results) const
{
	if (this->range() < 10)
		for (int i = 1; i <= 5; i++)
		{
			for (auto item : results)
				PrintLine(cout, item, i);
			cout << std::endl;
		}
	else
	{
		for (auto item : results)
			cout << "[" << std::setw(2) << item << "] ";
		cout << std::endl;
	}
}