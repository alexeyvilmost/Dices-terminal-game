#include <iostream>
#include <cmath>
#include "../includes/Dices.h"
#include "../includes/Game.h"
#include "../includes/Menu.h"

using std::cin;
using std::cout;
using std::string;

string	Intro()
{
	string command;
	system("clear");
	if (!command.empty())
		cout << "Error: Wrong command \"" << command << "\"\n";
	cout << "Hello, it's dices game.\n";
	cout << "Type " red "EXIT" endc ", if you want to exit\n";
	cout << "Type " blue "QUICK" endc ", if you wanna play quick game\n";
	cout << "Type " blue "CUSTOM" endc ", if you wanna customise your game\n";
	cout << "Type " blue "FILE filename" endc ", if you have a file with save\n";
	cin >> command;
	if (command == "CUSTOM" || command == "QUICK" || command == "EXIT" || command == "FILE")
		return command;
	return Intro();
}

int			main(void)
{
	string 			command;
	User			user;
	bool			restart;

	do
	{
		command = Intro();
		if (command == "QUICK")
		{
			cout << "Quick game started, good luck\n";
			restart = QuickGame(Game(user));
		}
		if (command == "CUSTOM")
			restart = CustomGame(user);
		else if (command == "FILE")
		{
			string	file;
			cout << "Enter a file where settings saved\n";
			cin >> file;
			std::ifstream	in(file);
			if (in)
				restart = CustomGame(user, in);
			else
				cerr << "Wrong file\n";
		} 
	}
	while (restart);
	return 0;
}

