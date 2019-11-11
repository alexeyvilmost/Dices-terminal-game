#pragma once

#include "Game.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include "utility.h"

using std::cin;
using std::cout;
using std::string;

bool		QuickGame(Game qGame);
bool		CustomGame(User &user, std::istream& in = cin);
Dices		DicesMenu(std::istream& in);
void		PointsMenu(User &user, std::istream& in);
void		AdvanceMenu(bool &skip, bool &color, std::istream& in);
void		SaveInter(std::ofstream& out, User &user, bool skip, bool color);