#pragma once
#include "pawn.h"
class board;
class queen : public soldier
{
public:
	queen();
public:
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	virtual void printSoldier();
};

