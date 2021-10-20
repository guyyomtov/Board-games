#pragma once	
#include "soldier.h"
class board;
class pawn : public soldier
{
public:
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing);
	void checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing);
	bool checkIfValidMove(int x, int y, int moveX, int moiveY, taken currPlayer,bool iEating, board& g_board, bool checkRiskOnKing);
	virtual void printSoldier();
};

