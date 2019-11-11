#include <vector>
#include <sstream>
#include <string>
#include "../includes/utility.h"

using namespace std;

int 	ParseInt(string inp, int from, int to)
{
	stringstream ss(inp);
	int ret;
	if (!(ss >> ret))
		throw invalid_argument("Wrong format - " + inp);
	if (ss.peek() != EOF)
		throw invalid_argument("Wrong format - " + inp);
	if (ret < from || ret > to)
		throw invalid_argument("Not in the current range:"
		" from " + to_string(from) + " to " + to_string(to) +
		"; \n" + "Your input" + " - " + inp);
	return ret;
}

bool 	countSeparator(int number, int range, int &answer)
{
	int temp = (range + 1) * number;
	answer = temp / 2;
	return temp % 2;
}

int		Sum(std::vector<int> const &result)
{
	int sum = 0;
	for (auto item : result)
		sum += item;
	return sum;
}