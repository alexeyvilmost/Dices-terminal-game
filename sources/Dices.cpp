//
// Created by alexeyvilmost on 28.10.2019.
//

#include <unistd.h>
#include "../includes/Dices.h"
#include "utility.h"

Dices::Dices(int range, int dices) :
				range_(range), dices_(dices), separator(0)
{
	this->in = countSeparator(dices_, range_, separator);
}

Dices::Dices(Dices const &other)
{
	range_ = other.range();
	dices_ = other.amount();
	history_ = other.history();
	this->in = countSeparator(dices_, range_, separator);
}

std::vector<int>	Dices::Throw(int prediction, bool color) const
{
	srand(time(nullptr));
	std::vector<int>	result(dices_);

	for (int last = 0; last < dices_; last++)
		for (int k = 0; k < 50; k++)
		{
			for (int flex = last; flex < dices_; flex++)
			{
				result[flex] = (rand() % range_) + 1;
			}

			PrintDice(result);
			PrintInfo(prediction,
					Sum(result, (k != 49) ? last : last + 1), color);

			if (last == dices_ - 1 && k == 49)
				break;
			usleep(50000);
			system("clear");
		}
	return result;
}

std::vector<int> Dices::ThrowSkip(int prediction, bool color) const
{
	srand(time(nullptr));
	std::vector<int>	result(dices_);

	for (auto &item : result)
		item = (rand() % range_) + 1;
	PrintDice(result);
	PrintInfo(prediction, Sum(result), color);
	return result;
}

int Dices::calculate(int prediction, int total) const
{
	if (prediction == total)
		return 1;
	if (prediction > separator && total > separator)
		return 0;
	if (in && prediction <= separator && total <= separator)
		return 0;
	if (!in && prediction < separator && total < separator)
		return 0;
	return -1;
}

int	Dices::Match(int prediction, bool skip, bool color)
{
	auto result = (skip) ? ThrowSkip(prediction, color) : Throw(prediction, color);
	history_.push_back({prediction, result});
	return calculate(prediction, Sum(result));
}

const Dices::results& Dices::history() const { return history_; }
int Dices::range() const { return range_; }
int Dices::amount() const { return dices_; }

void Dices::ChangeAmount(int amount) { dices_ = amount; }
void Dices::ChangeRange(int range) { range_ = range; }