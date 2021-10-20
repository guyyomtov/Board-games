#include "checkersKing.h"
#include "board.h"
void checkersKing::checkValidMove(int x, int y, board& g_board, bool withSoldier)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1,ind2) && g_board.getStatusOfSquare(ind1, ind2) == isValid::VALID && g_board.getTakenOfSquare(ind1, ind2) != taken::EMPTY)
	{
		if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL1) // i עולה 
		{
			checkKingCheckersMove(ind1, ind2, direction::DOWNRIGHT, g_board,taken::FULL2);
			checkKingCheckersMove(ind1, ind2, direction::DOWNLEFT, g_board,taken::FULL2);
			checkKingCheckersMove(ind1, ind2, direction::UPRIGHT,  g_board,taken::FULL2);
			checkKingCheckersMove(ind1, ind2, direction::UPLEFT, g_board,taken::FULL2);
		
		}
		//--------------------------------------------------------------------------------------------------------------------//
		else if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL2)
		{
			checkKingCheckersMove(ind1, ind2, direction::DOWNRIGHT, g_board, taken::FULL1);
			checkKingCheckersMove(ind1, ind2, direction::DOWNLEFT, g_board, taken::FULL1);
			checkKingCheckersMove(ind1, ind2, direction::UPRIGHT, g_board, taken::FULL1);
			checkKingCheckersMove(ind1, ind2, direction::UPLEFT, g_board, taken::FULL1);
		}

	}
	
}
void checkersKing::checkKingCheckersMove(int x, int y, direction currDir, board& g_board, taken opPlayer)
{
	int tmp = 1;
	bool isEating = false;

	switch (currDir)
	{
	case direction::DOWNRIGHT:
	{
		while (g_board.checkIfBound(x + tmp, y + tmp) && isEating == false)
		{
			if (checkIfValidMove(x + tmp, y + tmp, g_board) == false) //down right
			{
				if ((g_board.getTakenOfSquare(x + tmp, y + tmp) == opPlayer))
				{
					tmp++;
					checkIfValidMove(x + tmp, y + tmp, g_board);
					isEating = true;
				}
			}
			tmp++;
		}

		break;
	}
	case direction::DOWNLEFT:
	{
		while (g_board.checkIfBound(x + tmp, y - tmp) && isEating == false)
		{
			if (checkIfValidMove(x + tmp, y - tmp, g_board) == false) //down right
			{
				if ((g_board.getTakenOfSquare(x + tmp, y - tmp) == opPlayer))
				{
					tmp++;
					checkIfValidMove(x + tmp, y - tmp, g_board);
					isEating = true;
				}
			}
			tmp++;
		}

		break;
	}
	case direction::UPRIGHT:
	{
		while (g_board.checkIfBound(x - tmp, y + tmp) && isEating == false)
		{
			if (checkIfValidMove(x - tmp, y + tmp, g_board) == false) //down right
			{
				if ((g_board.getTakenOfSquare(x - tmp, y + tmp) == opPlayer))
				{
					tmp++;
					checkIfValidMove(x - tmp, y + tmp, g_board);
					isEating = true;
				}
			}
			tmp++;
		}

		break;
	}
	case direction::UPLEFT:
	{
		while (g_board.checkIfBound(x - tmp, y - tmp) && isEating == false)
		{
			if (checkIfValidMove(x - tmp, y - tmp, g_board) == false) //down right
			{
				if ((g_board.getTakenOfSquare(x - tmp, y - tmp) == opPlayer))
				{
					tmp++;
					checkIfValidMove(x - tmp, y - tmp, g_board);
					isEating = true;
				}
			}
			tmp++;
		}
		break;
	}

	}
}
bool checkersKing::checkIfValidMove(int x, int y, board& g_board)
{
	if (g_board.checkIfBound(x, y))
	{
		if (g_board.getTakenOfSquare(x, y) == taken::EMPTY)
		{
			s_listOfValidMoves.push_back(g_board.getSquare(x, y)); // maybe reference?
			return true;
		}
	}
	return false;

}

void checkersKing::printSoldier()
{
	cout << "O";
}
