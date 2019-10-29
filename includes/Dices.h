//
// Created by alexeyvilmost on 28.10.2019.
//

#ifndef DICES_H
#define DICES_H

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <cstdlib>

class Dices
{
public:
		using		throw_ = typename std::vector<int>;
		using 		result = typename std::pair<int, throw_>; // {pred, results}
		using 		results = typename std::vector<result>;
		using 		stream = typename std::ostream&;

					Dices(int range = 6, int dices = 2);
					Dices(Dices const &other);
		int 		Match(int prediction, bool skip = false);
		int			calculate(int prediction, int res) const;
		void		ChangeRange(int range);
		void 		ChangeAmount(int amount);

const	results&	history() const;
		int			range() const;
		int			amount() const;
private:
		throw_ 		Throw(int prediction) const;
		throw_ 		ThrowSkip(int prediction) const;
		void 		PrintDice(std::vector<int> const &result) const;
		void 		PrintInfo(int prediction, int sum) const;

		int			separator;
		bool		in;
		int			range_;
		int			dices_;
		results		history_;
};


#endif
