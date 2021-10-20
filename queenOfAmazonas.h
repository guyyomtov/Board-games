#pragma once
class soldier;
class board;
class game;
#include "knight.h"
class queenOfAmazonas : public soldier
{
public:
	virtual void checkValidMove(int x, int y, board& g_board, bool withSoldier);
	bool checkIfValidMove(int x, int y, bool withSoldier, board& g_board);
	void checkPossibleMove(int x, int y, direction currDir, bool withSoldier, board& g_board);
	virtual void printSoldier();

};

