#include "queen.h"
#include "board.h"

queen::queen()
{
}

void queen::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::DOWNRIGHT,g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWNLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWN, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::RIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::LEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UP, g_board, checkRiskOnKing);
	}
}

void queen::printSoldier()
{
	cout << "Q";
}

