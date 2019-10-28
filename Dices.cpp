#include <iostream>
#include <cmath>
#include <utility>

int			ThrowDice(void)
{
	return (std::rand() % 6 + 1);
}

class UserInterface
{
private:
	int score = 0;
	int turn = 0;
	std::vector<std::pair<int, int>>		turns;
public:
	UserInterface(int score);
	~UserInterface();
	
};

int			main(void)
{
	int	score = 100;
	int	bet = 0;

	system("clear");
	while (score > 0 && score < 500)
	{
		int sum;
		int result;
		
		cout << "Your current score: " << score << endl;
		cout << "Enter your bet: " << endl;
		cin >> bet;
		cout << "Choose your dices sum: " << endl;
		cin >> sum;
		
		if (sum < 2 || sum > 12 || bet > score || bet < 0)
		{
			cout << "This input incorrect" << endl;
			continue ;
		}
		result = ThrowDice() + ThrowDice();
		if (result == sum)
			score += 8 * bet;
		else if (!((result > 7 && sum > 7) || (result < 7 && sum < 7)))
			score -= bet;
		system("clear");
		cout << "Your prediction: " << sum << endl << "Result on dices: " << result << endl;
	}
	if (score == 0)
		cout << "You lose" << endl;
	else
		cout << "You win with " << score << " points" << endl;
}