#pragma once
#include "king.h"
class board;
class knight : public soldier
{
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	void checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing);
	virtual void printSoldier();
};
