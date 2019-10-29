#include <vector>

bool 	countSeparator(int number, int range, int &answer)
{
	int temp = (range + 1) * number;
	answer = temp / 2;
	return temp % 2;
}

int		Sum(std::vector<int> const &result, size_t j = 0)
{
	int sum = 0;
	if (!j)
		j = result.size();
	for (size_t i = 0; i < j; i++)
		sum += result[i];
	return sum;
}