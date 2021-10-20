#pragma once
#include "checkersSoldier.h"
class board;
class checkersKing : public soldier
{
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	void checkKingCheckersMove(int x, int y, direction currDir, board& g_board, taken opPlayer);
	bool checkIfValidMove(int x, int y, board& g_board);
	void printSoldier();

};

