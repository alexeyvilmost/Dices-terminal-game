#include "../includes/Menu.h"

void		QuickGame(Game qGame)
{
	while (qGame.turn()); // All interaction game happens in this line

	string command;
	cout << "If you want to see game history, type " << qGame.cm("PRINT") << "\n";
	cout << "It you want to save game history in file, type " << qGame.cm("FILE filename") << "\n";
	cout << "If you want to quit, type anything else\n";
	cin >> command;
	if (command == "FILE")
	{
		string temp;
		cin >> temp;
		std::ofstream	out(temp);
		if (out)
		{
			qGame.color = false;
			qGame.PrintHistory(out);
			cout << "History was recorded in " << temp << "\n";
		}
		else
		{
			cout << "Error: can't reach file, printing on screen" << "\n";
			command = "PRINT";
		}
	}
	if (command == "PRINT")
		qGame.PrintHistory(cout);
}

void	CustomGame(User &user, std::istream& in)
{
	string		command;
	bool			skip = false;
	bool			color = true;
	while (true)
	{
		system("clear");
		if (!command.empty())
			cout << "UNKNOWN COMMAND: " << command << std::endl;
		cout << "Welcome to customise menu, select an option\n";
		cout << blue "DICES" endc " if you want to change dices settings\n";
		cout << blue "POINTS" endc " if you want to change start points or win condition\n";
		cout << blue "ADVANCE" endc " if you want to disable advance settings\n";
		cout << blue "SAVE filename" endc " to save this changes to file\n";
		cout << blue "START" endc " to start the game with selected settings\n";
		in >> command;
		if (command == "START")
			break;
		if (command == "DICES")
		{
			user.dices = DicesMenu(in);
		}
		if (command == "POINTS")
			PointsMenu(user, in);
		if (command == "ADVANCE")
			AdvanceMenu(skip, color, in);
		else if (command == "SAVE")
		{
			string	filename;
			cin >> filename;
			std::ofstream	out(filename);
			if (out)
				SaveInter(out, user, skip, color);
			else
				cout << "Can't reach file " << filename << " \n";
		}
	}

	Game	Custom(user, skip, color);
	cout << "Custom game started, good luck\n";
	QuickGame(Custom);
}