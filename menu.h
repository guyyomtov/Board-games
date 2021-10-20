#pragma once
#include "circularList.h"
#include <fstream>
class chess;
class amazonas;
class checkers;
/*The menu response to get valid input and to print error message.*/
class menu {

public:
	menu();
	~menu();
	void printMenu();
	void afterUserSelect();
	void start_Game();
	void startGame();
	bool checkIfGameIsOn();
	void getInput(int& x, int& y);
	void getWhereToDart(int toX, int toY);
	bool theGameIsOver();
	void choseGame();
	game* getDetailOnGameAndAllocate(ifstream& inFile);
	bool checkOpeningFile(ifstream& inFile);
	bool checkOpeningFile(ofstream& inFile);

private:
	circularList listGames;
	game* lastGame;
	bool gameStart = false;
	bool exit;
	int userSelection;
	game* curGame;
};
