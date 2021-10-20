#pragma once
#include "queenOfAmazonas.h"
class board;
class checkersSoldier : public soldier
{
public:
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	bool checkIfValidMove(int x, int y, board& g_board);
	virtual void printSoldier();

};

