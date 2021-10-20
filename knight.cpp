#include "knight.h"
#include "board.h"
void knight::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::UPRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::RIGHTUP, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::RIGHTDOWN, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWNRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWNLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::LEFTDOWN, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::LEFTUP, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPLEFT, g_board, checkRiskOnKing);
	}														 
}
//the first diretion indicates the first two-square move, the second one is the one-square move
void knight::checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing)
{
	int firstMove = 2, secondMove = 1;
	taken currPlayer = g_board.getTakenOfSquare(x, y);
	switch (currDir)
	{
	case direction::UPRIGHT:
	{
		if (g_board.checkIfBound(x - firstMove, y + secondMove) && !checkIfValidMove(x, y,x - firstMove, y + secondMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::RIGHTUP:
	{
		if (g_board.checkIfBound(x - secondMove, y + firstMove) && !checkIfValidMove(x, y,x - secondMove, y + firstMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::RIGHTDOWN:
	{
		if (g_board.checkIfBound(x + secondMove, y + firstMove) && !checkIfValidMove(x, y,x + secondMove, y + firstMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::DOWNRIGHT:
	{
		if (g_board.checkIfBound(x + firstMove, y + secondMove) && !checkIfValidMove(x, y, x + firstMove, y + secondMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::DOWNLEFT:
	{
		if (g_board.checkIfBound(x + firstMove, y - secondMove) && !checkIfValidMove(x, y, x + firstMove, y - secondMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::LEFTDOWN:
	{
		if (g_board.checkIfBound(x + secondMove, y - firstMove) && !checkIfValidMove(x, y, x + secondMove, y - firstMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::LEFTUP:
	{
		if (g_board.checkIfBound(x - secondMove, y - firstMove) && !checkIfValidMove(x, y, x - secondMove, y - firstMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}
	case direction::UPLEFT:
	{
		if (g_board.checkIfBound(x - firstMove, y - secondMove) && !checkIfValidMove(x, y, x - firstMove, y - secondMove, currPlayer, g_board, checkRiskOnKing)){}
			break;
	}

	}
}

void knight::printSoldier()
{
	cout << "H";
}
