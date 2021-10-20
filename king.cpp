#include "king.h"
#include "board.h"
#include "soldier.h"
void king::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::DOWNRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWNLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWN, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::RIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::LEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UP, g_board, checkRiskOnKing);
	}
}
//-----------------------------------------------------------------------------------------------------------------------//
void king::checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing)
{
	int move = 1;
	taken currPlayer = g_board.getTakenOfSquare(x, y);
	switch (currDir)
	{
	case direction::DOWNRIGHT:
	{
		if (g_board.checkIfBound(x + move, y + move) && !checkIfValidMove(x, y, x + move, y + move, currPlayer, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::DOWNLEFT:
	{
		if (g_board.checkIfBound(x + move, y - move) && !checkIfValidMove(x, y, x + move, y - move, currPlayer, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::UPRIGHT:
	{
		if (g_board.checkIfBound(x - move, y + move) && !checkIfValidMove(x, y, x - move, y + move, currPlayer, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::UPLEFT:
	{
		if (g_board.checkIfBound(x - move, y - move) && !checkIfValidMove(x, y, x - move, y - move, currPlayer, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::UP:
	{
		if (g_board.checkIfBound(x - move, y) && !checkIfValidMove(x, y, x - move, y, currPlayer, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::LEFT:
	{
		if (g_board.checkIfBound(x, y - move) && !checkIfValidMove(x, y, x, y - move, currPlayer, g_board, checkRiskOnKing))
		{ }
		break;
	}
	case direction::DOWN:
	{
		if (g_board.checkIfBound(x + move, y) && !checkIfValidMove(x, y, x + move, y, currPlayer, g_board, checkRiskOnKing))
		{ }
		break;
	}
	case direction::RIGHT:
	{
		if (g_board.checkIfBound(x, y + move) && !checkIfValidMove(x, y, x, y + move, currPlayer, g_board, checkRiskOnKing))
		{ }
		break;
	}

	}
}

void king::printSoldier()
{
	cout << "K";
}

