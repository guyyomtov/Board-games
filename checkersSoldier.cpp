#include "checkersSoldier.h"
#include "board.h"

void checkersSoldier::checkValidMove(int x, int y, board& g_board, bool withSoldier)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2) && g_board.getStatusOfSquare(ind1, ind2) == isValid::VALID && g_board.getTakenOfSquare(ind1, ind2) != taken::EMPTY)
	{
		if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL1) // i עולה 
		{
				if (checkIfValidMove(ind1 + 1, ind2 - 1, g_board) == false) //down left
				{
					if (g_board.checkIfBound(ind1 + 1, ind2 - 1) && (g_board.getTakenOfSquare(ind1 + 1, ind2 - 1) == taken::FULL2))
						checkIfValidMove(ind1 + 2, ind2 - 2, g_board);
				}
				if (checkIfValidMove(ind1 + 1, ind2 + 1, g_board) == false) //down right
				{
					if (g_board.checkIfBound(ind1 + 1, ind2 + 1) && (g_board.getTakenOfSquare(ind1 + 1, ind2 + 1) == taken::FULL2))
						checkIfValidMove(ind1 + 2, ind2 + 2, g_board);
				}

		}
		else if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL2)
		{
				if (checkIfValidMove(ind1 - 1, ind2 - 1, g_board) == false) //up left
				{
					if (g_board.checkIfBound(ind1 - 1, ind2 - 1)&&(g_board.getTakenOfSquare(ind1 - 1, ind2 - 1) == taken::FULL1))
						checkIfValidMove(ind1 - 2, ind2 - 2, g_board);
				}
				if (checkIfValidMove(ind1 - 1, ind2 + 1, g_board) == false) //up right
				{
					if (g_board.checkIfBound(ind1 - 1, ind2 + 1) && (g_board.getTakenOfSquare(ind1 - 1, ind2 + 1) == taken::FULL1))
						checkIfValidMove(ind1 - 2, ind2 + 2, g_board);
				}
		
		}
	}
}
	
bool checkersSoldier::checkIfValidMove(int x, int y, board& g_board)
{
	if (g_board.checkIfBound(x,y))
	{
		if (g_board.getTakenOfSquare(x, y) == taken::EMPTY)
		{
			s_listOfValidMoves.push_back(g_board.getSquare(x, y)); // maybe reference?
			return true;
		}
		else
			return false;
	}
	return false;

}

void checkersSoldier::printSoldier()
{
	cout << "o";
}
