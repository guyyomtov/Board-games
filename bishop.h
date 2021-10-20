#pragma once
#include "queen.h"
class board;
class bishop : public soldier
{
public:
	virtual void checkValidMove(int x, int y, board& board, bool checkRiskOnKing);
	virtual void printSoldier();
};
