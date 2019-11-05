#include "../includes/Menu.h"

bool	is(bool condition)
{
	if (!condition) cout << "Argument is invalid, try again" << std::endl;
	return condition;
}

Dices	DicesMenu(std::istream& in)
{
	Dices			custom;
	string			command;
	int				d_argument;
	while (true)
	{
		system("clear");
		cout << "Select an option:\n";
		cout << blue "AMOUNT number " endc "to change number of dices (1-7)\n";
		cout << blue "RANGE number " endc "to change number of faces (1-20)\n";
		cout << red "EXIT " endc "to go back and apply settings\n";
		in >> command;
		if (command == "EXIT")
		{
			cout << "New dices settings: range - " << custom.range()
				 << "; amount - " << custom.amount() << ";" << std::endl;
			return custom;
		}
		if (command == "AMOUNT")
		{
			in >> d_argument;
			system("clear");
			if (is(d_argument > 0 && d_argument < 8))
			{
				cout << "Amount of dices changed from " << custom.amount()
					 << " to " << d_argument << std::endl;
				custom.ChangeAmount(d_argument);
			}
		}
		else if (command == "RANGE")
		{
			in >> d_argument;
			system("clear");
			if (is(d_argument > 0 && d_argument < 21))
			{
				cout << "Range of dices changed from " << custom.range()
					 << " to " << d_argument << std::endl;
				custom.ChangeRange(d_argument);
			}
		}
		else
		{
			system("clear");
			cout << "UNKNOWN COMMAND: " << command << std::endl;
		}
		wait;
	}
}

void	PointsMenu(User &user, std::istream& in)
{
	string		command;
	int				argument;
	while (true)
	{
		system("clear");
		cout << "Select an option:\n";
		cout << blue "START number " endc "to change start points (1-win)\n";
		cout << blue "WIN number " endc "to change points, required for win (start-10000)\n";
		cout << red "EXIT " endc "to go back and apply settings\n";
		in >> command;
		if (command == "EXIT")
		{
			cout << "New points settings: start - " << user.points
				 << "; win - " << user.win_condition << ";" << std::endl;
			wait;
			return ;
		}
		if (command == "START")
		{
			in >> argument;
			system("clear");
			if (is(argument > 0 && argument < user.win_condition))
			{
				cout << "Start points changed from " << user.points << " to " << argument << std::endl;
				user.points = argument;
			}
		}
		else if (command == "WIN")
		{
			in >> argument;
			system("clear");
			if (is(argument > user.points && argument <= max_win))
			{
				cout << "Win points changed from " << user.win_condition
					 << " to " << argument << std::endl;
				user.win_condition = argument;
			}
		}
		else
		{
			system("clear");
			cout << "UNKNOWN COMMAND: " << std::endl;
		}
		wait;
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