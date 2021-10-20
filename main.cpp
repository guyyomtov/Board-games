#include "menu.h"
//We know that check if bounds should be in the board but we want to make the right execption 
//and we still didnt learn try and catch so we make check if bounds in the menu for execption 
//and check if bound in the board!
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

