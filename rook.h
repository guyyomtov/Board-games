#pragma once
#include "bishop.h"
class board;
class soldier;
class rook : public soldier
{
public:
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	virtual void printSoldier();
};
