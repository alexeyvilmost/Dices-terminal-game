#include <vector>

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