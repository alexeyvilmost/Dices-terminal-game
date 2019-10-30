#include <iostream>
#include <cmath>
#include <utility>
#include <unistd.h>
#include "../includes/Dices.h"
#include "../includes/Game.h"
#include "utility.h"

std::string	Intro()
{
	std::string command;
	system("clear");
	if (!command.empty())
		std::cout << "Error: Wrong command \"" << command << "\"\n";
	std::cout << "Hello, it's dices game.\n";
	std::cout << "Type " red "EXIT" endc ", if you want to exit\n";
	std::cout << "Type " blue "QUICK" endc ", if you wanna play quick game\n";
	std::cout << "Type " blue "CUSTOM" endc ", if you wanna customise your game\n";
	std::cout << "Type " blue "FILE filename" endc ", if you have a file with save\n";
	std::cin >> command;
	if (command == "CUSTOM" || command == "QUICK" || command == "EXIT" || command == "FILE")
		return command;
	return Intro();
}

void		QuickGame(Game qGame)
{
	std::string		temp_command;

	while (qGame.turn());
	std::cout << "If you want to see game history, type " << qGame.cm("PRINT") << "\n";
	std::cout << "It you want to save game history in file, type " << qGame.cm("FILE filename") << "\n";
	std::cout << "If you want to quit, type anything else\n";
	std::cin >> temp_command;
	if (temp_command == "FILE")
	{
		std::string temp;
		std::cin >> temp;
		std::ofstream	out(temp);
		if (out)
		{
			qGame.color = false;
			qGame.PrintHistory(out);
			std::cout << "History was recorded in " << temp << "\n";
		}
		else
		{
			std::cout << "Error: can't reach file, printing on screen" << "\n";
			temp_command = "PRINT";
		}
	}
	if (temp_command == "PRINT")
		qGame.PrintHistory(std::cout);
}

bool	is(bool condition)
{
	if (!condition)
		std::cout << "Argument is invalid, try again" << std::endl;
	return condition;
}

Dices	DicesMenu(std::istream& in)
{
	Dices			custom;
	std::string		d_command;
	int				d_argument;
	while (true)
	{
		system("clear");
		std::cout << "Select an option:\n";
		std::cout << blue "AMOUNT number " endc "to change number of dices (1-7)\n";
		std::cout << blue "RANGE number " endc "to change number of faces (1-20)\n";
		std::cout << red "EXIT " endc "to go back and apply settings\n";
		in >> d_command;
		if (d_command == "EXIT")
			return custom;
		if (d_command == "AMOUNT")
		{
			in >> d_argument;
			system("clear");
			if (is(d_argument > 0 && d_argument < 8))
			{
				std::cout << "Amount of dices changed from " << custom.amount() 
				<< " to " << d_argument << std::endl;
				custom.ChangeAmount(d_argument);
			}
			usleep(1000000);
		}
		else if (d_command == "RANGE")
		{
			in >> d_argument;
			system("clear");
			if (is(d_argument > 0 && d_argument < 21))
			{
				std::cout << "Range of dices changed from " << custom.range() 
				<< " to " << d_argument << std::endl;
				custom.ChangeRange(d_argument);
			}
			usleep(1000000);
		}
		else
		{
			system("clear");
			std::cout << "UNKNOWN COMMAND: " << d_command << std::endl;
			usleep(1000000);
		}
	}
}

void	PointsMenu(User &user, std::istream& in)
{
	std::string		command;
	int				argument;
	while (true)
	{
		system("clear");
		std::cout << "Select an option:\n";
		std::cout << blue "START number " endc "to change start points (1-win)\n";
		std::cout << blue "WIN number " endc "to change points, required for win (start-10000)\n";
		std::cout << red "EXIT " endc "to go back and apply settings\n";
		in >> command;
		if (command == "EXIT")
			return ;
		if (command == "START")
		{
			in >> argument;
			system("clear");
			if (is(argument > 0 && argument < user.win_condition))
			{
				std::cout << "Start points changed from " << user.points << " to " << argument << std::endl;
				user.points = argument;
			}
			usleep(1000000);
		}
		else if (command == "WIN")
		{
			in >> argument;
			system("clear");
			if (is(argument > user.points && argument < 10001));
			{
				std::cout << "Win points changed from " << user.win_condition 
				<< " to " << argument << std::endl;
				user.win_condition = argument;
			}
			usleep(1000000);
		} 
		else
		{
			system("clear");
			std::cout << "UNKNOWN COMMAND: " << std::endl;
			usleep(1000000);
		}
	}
}

void	AdvanceMenu(bool &skip, bool &color, std::istream& in)
{
	std::string command;
	while (true)
	{
		system("clear");
		std::cout << "Select an option:\n";
		std::cout << blue "COLOR " endc "to change color mode, now - ";
		if (color)
			std::cout << green "enabled\n";
		else
			std::cout << red "disabled\n";
		std::cout << blue "SKIP " endc "to change skip mode, now - ";
		if (skip)
			std::cout << green "enabled\n";
		else
			std::cout << red "disabled\n";
		std::cout << red "EXIT " endc "to go back and apply settings\n";
		in >> command;

		if (command == "EXIT")
			return;
		if (command == "SKIP")
			skip = !skip;
		if (command == "COLOR")
			color = !color;
	}
}

void	SaveInter(std::ofstream& out, User &user, bool skip, bool color)
{
	if (user.dices.amount() != 2 || user.dices.range() != 6)
	{
		out << "DICES ";
		if (user.dices.amount() != 2)
			out << "AMOUNT " << user.dices.amount() << " ";
		if (user.dices.range() != 6)
			out << "RANGE " << user.dices.range() << " ";
		out << "EXIT ";
	}
	if (user.points != 100 || user.win_condition != 500)
	{
		out << "POINTS ";
		if (user.win_condition <= 100)
			out << "START " << user.points << " ";
		
		out << "WIN " << user.win_condition << " ";
		
		if (user.win_condition > 100)
			out << "START " << user.points << " ";
		out << "EXIT ";
	}
	if (skip || !color)
	{
		out << "ADVANCE ";
		if (skip)
			out << "SKIP ";
		if (!color)
			out << "COLOR ";
		out << "EXIT";
	}
	out << "START\n";
	std::cout << "Save successfull\n";
}

void	CustomGame(User &user, std::istream& in)
{
	std::string		command;
	bool			skip = false;
	bool			color = true;
	while (true)
	{
		system("clear");
//		if (!command.empty())
//			std::cout << "UNKNOWN COMMAND: " << command << std::endl;
		std::cout << "Welcome to customise menu, select an option\n";
		std::cout << blue "DICES" endc " if you want to change dices settings\n";
		std::cout << blue "POINTS" endc " if you want to change start points or win condition\n";
		std::cout << blue "ADVANCE" endc " if you want to disable advance settings\n";
		std::cout << blue "SAVE filename" endc " to save this changes to file\n";
		std::cout << blue "START" endc " to start the game with selected settings\n";
		in >> command;
		if (command == "START")
			break;
		if (command == "DICES")
		{
			user.dices = DicesMenu(in);
			std::cout << "New dices settings: range - " << user.dices.range()
					<< "; amount - " << user.dices.amount() << ";" << std::endl;
		}
		if (command == "POINTS")
		{
			PointsMenu(user, in);
			std::cout << "New points settings: start - " << user.points
					  << "; win - " << user.win_condition << ";" << std::endl;
		}
		if (command == "ADVANCE")
		{
			AdvanceMenu(skip, color, in);
		}
		else if (command == "SAVE")
		{
			std::string	filename;
			std::cin >> filename;
			std::ofstream	out(filename);
			if (out)
				SaveInter(out, user, skip, color);
			else
				std::cout << "Can't reach file " << filename << " \n";
		}
	}

	Game	Custom(user, skip, color);
	std::cout << "Custom game started, good luck\n";
	QuickGame(Custom);
}

int			main(void)
{
	std::string 	command = Intro();
	User			user;

	if (command == "QUICK")
	{
		std::cout << "Quick game started, good luck\n";
		QuickGame(Game(user));
	}
	if (command == "CUSTOM")
		CustomGame(user, std::cin);
	else if (command == "FILE")
	{
		std::string	file;
		std::cout << "Enter a file where settings saved\n";
		std::cin >> file;
		std::ifstream	in(file);
		if (in)
			CustomGame(user, in);
		else
			std::cout << "Wrong file\n";
	}
	return 0;
}
