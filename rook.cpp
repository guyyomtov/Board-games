#include "rook.h"
#include "board.h"
#include "soldier.h"

void rook::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::DOWN, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::RIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::LEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UP, g_board, checkRiskOnKing);
	}
}

void rook::printSoldier()
{
	cout << "R";
}
