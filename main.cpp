#include "menu.h"

void main()
{
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		menu m;
		m.startGame();
	}
	int x = 5;
}

