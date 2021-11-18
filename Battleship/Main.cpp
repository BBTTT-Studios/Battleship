/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : Main.cpp
Description : Initial start file. Handles option menu
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

#define NOMINMAX

#include "CGameManager.h"
#include "termcolor.hpp"

using namespace std;

void PrintTitle();

template<typename T>
static T& ValidateInput(T& val)
{
	while (true) {
		if (!(std::cin >> val))
		{
			std::cout << "Enter a valid value!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}
	return val;
}



//MAIN GAME FUNCTION
int main()
{
	while (true)
	{
		int choice;
	
		PrintTitle();
		cout << "  1: Single Player" << endl;
		cout << "  2: Debug Mode" << endl;
		cout << "  3: Credits" << endl;
		cout << "  4: Quit" << endl << endl;

		cout << "Option: ";

		ValidateInput(choice);

		switch (choice)
		{
		case 1:
			{
				CGameManager SPGameManager = CGameManager(true);
			}
			break;

		case 2:
			{
				CGameManager MPGameManager = CGameManager(false);
			}
			break;

		case 3:
			system("cls");
			cout << termcolor::yellow << "Credits:" << endl << "==============" << termcolor::reset << endl << endl;
			cout << "Creator: Vinnie Gray" << endl << endl;
			cout << "Terminal Colours: Ihor Kalnytskyi" << endl << "https://github.com/ikalnytskyi/termcolor" << endl << endl;
			system("pause");
			system("cls");
			break;

		case 4:
			exit(1);

		default:
			system("cls");
			cout << "Invalid Option";
		}
	}
	
	
}

void PrintTitle()
{
	cout << termcolor::yellow <<
		"  ____        _   _   _           _     _            \n"
		" |  _ \\      | | | | | |         | |   (_)           \n"
		" | |_) | __ _| |_| |_| | ___  ___| |__  _ _ __  ___  \n"
		" |  _ < / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\/ __| \n"
		" | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) \\__ \\ \n"
		" |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/|___/ \n"
		"                                         | |         \n"
		"                                         |_|         \n" << termcolor::reset << endl;
	
}