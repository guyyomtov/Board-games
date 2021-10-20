#include "bishop.h"
#include "board.h"
void bishop::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::DOWNRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::DOWNLEFT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPRIGHT, g_board, checkRiskOnKing);
		checkPossibleMove(ind1, ind2, direction::UPLEFT, g_board, checkRiskOnKing);
	}
}

void bishop::printSoldier()
{
	cout << "B";
}
