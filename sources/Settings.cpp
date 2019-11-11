#include "../includes/Menu.h"

#include <string>

using namespace std;

Dices	DicesMenu(std::istream& in)
{
	Dices			custom;
	string			command;
	int				d_argument;
	while (true)
	{
		cout << "Select an option:\n";
		cout << blue "AMOUNT number " endc "to change number of dices (1-7)\n";
		cout << blue "RANGE number " endc "to change number of faces (1-20)\n";
		cout << red "EXIT " endc "to go back and apply settings" << endl;
		in >> command;

		if (command == "EXIT")
		{
			cout << "New dices settings: range - " << custom.range()
				 << "; amount - " << custom.amount() << ";" << std::endl;
			return custom;
		}
		try 
		{
			if (command == "AMOUNT")
			{
				string temp;
				in >> temp;
				d_argument = ParseInt(temp, 1, 7);
				cout << "Amount of dices changed from " << custom.amount()
					 << " to " << d_argument << std::endl;
				custom.ChangeAmount(d_argument);
			}
			else if (command == "RANGE")
			{
				string temp;
				in >> temp;
				d_argument = ParseInt(temp, 1, 20);
				cout << "Range of dices changed from " << custom.range()
					 << " to " << d_argument << std::endl;
				custom.ChangeRange(d_argument);
			}
			else
				cerr << "UNKNOWN COMMAND: " << command << endl;
		}
		catch (invalid_argument& arg)
		{
			cerr << arg.what() << endl;
		}
		system("clear");
	}
}

void	PointsMenu(User &user, std::istream& in)
{
	string		command;
	string		arg_str;
	int 		arg_val;
	while (true)
	{
		cout << "Select an option:\n";
		cout << blue "START number " endc "to change start points (1-" << user.win_condition << ")\n";
		cout << blue "WIN number " endc "to change points, required for win (" << user.points << "-10000)\n";
		cout << red "EXIT " endc "to go back and apply settings\n";
		in >> command;
		if (command == "EXIT")
		{
			cout << "New points settings: start - " << user.points
				 << "; win - " << user.win_condition << ";" << std::endl;
			wait;
			return ;
		}
		try {
			if (command == "START")
			{
				in >> arg_str;
				arg_val = ParseInt(arg_str, 1, user.win_condition);
				cout << "Start points changed from " << user.points << " to " << arg_val << std::endl;
				user.points = arg_val;
			}
			else if (command == "WIN")
			{
				in >> arg_str;
				arg_val = ParseInt(arg_str, user.points, max_win);
				cout << "Win points changed from " << user.win_condition
					 << " to " << arg_val << std::endl;
				user.win_condition = arg_val;
			}
			else
				cerr << "UNKNOWN COMMAND: " << endl;
		}
		catch (invalid_argument& arg)
		{
			cerr << arg.what() << endl;
		}
		system("clear");
	}
}

void	AdvanceMenu(bool &skip, bool &color, std::istream& in)
{
	string command;
	while (true)
	{
		system("clear");
		cout << "Select an option:\n";
		cout << blue "COLOR " endc "to change color mode, now - ";
		if (color)
			cout << green "enabled\n";
		else
			cout << red "disabled\n";
		cout << blue "SKIP " endc "to change skip mode, now - ";
		if (skip)
			cout << green "enabled\n";
		else
			cout << red "disabled\n";
		cout << red "EXIT " endc "to go back and apply settings\n";
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
		out << "AMOUNT " << user.dices.amount() << " ";
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
		if (skip) out << "SKIP ";
		if (!color) out << "COLOR ";
		out << "EXIT";
	}
	out << "START\n";
	cout << green "Save successfull\n" endc;
	wait;
}