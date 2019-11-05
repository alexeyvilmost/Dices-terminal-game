#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>

class Dices
{
public:
		using		throw_ = typename std::vector<int>;
		using 		result = typename std::pair<int, throw_>; // {pred, results}
		using 		results = typename std::vector<result>;
		using 		stream = typename std::ostream&;
		using		probability = typename std::vector<double>;

		explicit	Dices(int range = 6, int dices = 2); //Constructor from 0-2 args, range and amount
					Dices(Dices const &other); //Copy constructor for custom settings supply
		int 		Match(int prediction, bool skip = false, bool color = true); //Main interface to interact
		int			calculate(int prediction, int res) const; //Additional functon, works like Match, but w/o Throw()
		void		ChangeRange(int range); //Functions to change basic fields
		void 		ChangeAmount(int amount);
		double		operator[](size_t i) const;

const	results&	history() const; //Function to get history of throws
		int			range() const;
		int			amount() const;
private:
		throw_ 		Throw(int prediction, bool color) 				const; //Make basic throw with animation
		throw_ 		ThrowSkip(int prediction, bool color) 			const; //Make throw w/o animation
		void 		PrintDice(std::vector<int> const &result) 		const; //Prints dices by throw data
		void 		PrintInfo(int prediction, int sum, bool color)	const; //Prints additional info for user
		void		calculateProb();

		int			separator; //Calculating automaticly
		bool		in; //Represent, if separator in or out of range
		int			range_; //Range of dice
		int			dices_; //Number of dices
		results		history_; //History of throws
		probability probab;
};