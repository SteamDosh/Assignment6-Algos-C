#include "Functions.h"
#include <iostream>
#include <cctype>
using namespace std;

char Menu();

int main()
{
	bool Quit = false;

	do
	{
		char Cmd = Menu();
		switch (Cmd)
		{
			case 'r':
				SelectFile();
				break;
			case 'd':
				break;
			case 'q':
				Quit = true;
				break;
			default:
				cerr << "Invalid command!\n";
		}
	} while (!Quit);

	return 0;
}

char Menu()
{
	char Cmd;
	cout << endl << "*********************************" << endl;
	cout << "*     Rabin-Karp Algo           *" << endl;
	cout << "*     (r)ead file               *" << endl;
	cout << "*     (q)uit                    *" << endl;
	cout << "*********************************" << endl;
	cout << "Command: ";
	cin >> Cmd;
	cin.ignore();  // eat up '\n'
	Cmd = tolower(Cmd);
	return Cmd;
}