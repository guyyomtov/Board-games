#include "pawn.h"
#include "board.h"
void pawn::checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing)
{
	int  ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL1) //for player1
		{
			checkPossibleMove(ind1, ind2, direction::DOWN, g_board, checkRiskOnKing);
			checkPossibleMove(ind1, ind2, direction::DOWNLEFT, g_board, checkRiskOnKing);
			checkPossibleMove(ind1, ind2, direction::DOWNRIGHT, g_board, checkRiskOnKing);
		}
		else if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL2) // for player2
		{					
			checkPossibleMove(ind1, ind2, direction::UP, g_board, checkRiskOnKing);
			checkPossibleMove(ind1, ind2, direction::UPLEFT, g_board, checkRiskOnKing);
			checkPossibleMove(ind1, ind2, direction::UPRIGHT, g_board, checkRiskOnKing);
		}
	}
}

void pawn::checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing)
{
	int move = 1;
	bool startingPos = false;
	if ((x == 1 && g_board.getTakenOfSquare(x, y) == taken::FULL1))
		startingPos = true;
	if((x == 6 && g_board.getTakenOfSquare(x, y) == taken::FULL2))
		startingPos = true;

	taken currPlayer = g_board.getTakenOfSquare(x, y);
	switch (currDir)
	{
	case direction::DOWNRIGHT:
	{
		if (g_board.checkIfBound(x + move, y + move) && checkIfValidMove(x, y, x + move, y + move, currPlayer, true, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::DOWNLEFT:
	{
		if (g_board.checkIfBound(x + move, y - move) && checkIfValidMove(x, y, x + move, y - move, currPlayer, true, g_board, checkRiskOnKing))
		{}
		break;
	}
	case direction::UPRIGHT:
	{
		if (g_board.checkIfBound(x - move, y + move) && checkIfValidMove(x, y, x - move, y + move, currPlayer,true, g_board, checkRiskOnKing))
		{ }
		break;
	}
	case direction::UPLEFT:
	{
		if (g_board.checkIfBound(x - move, y - move) && checkIfValidMove(x, y, x - move, y - move, currPlayer, true, g_board, checkRiskOnKing))
		{ }
		break;
	}
	case direction::UP:
	{
		if (g_board.checkIfBound(x - move, y) && checkIfValidMove(x, y, x - move, y, currPlayer, false, g_board, checkRiskOnKing) && startingPos)
		{
			++move;
			if (g_board.checkIfBound(x - move, y) && checkIfValidMove(x, y, x - move, y, currPlayer, false, g_board, checkRiskOnKing))
				startingPos = false;
		}
		break;
	}
	case direction::DOWN:
	{
		if (g_board.checkIfBound(x + move, y) && checkIfValidMove(x, y, x + move, y, currPlayer, false, g_board, checkRiskOnKing) && startingPos)
		{
			++move;
			if (g_board.checkIfBound(x + move, y) && checkIfValidMove(x, y, x + move, y, currPlayer, false, g_board, checkRiskOnKing))
				startingPos = false;		
		}
		break;
	}
	}
}

bool pawn::checkIfValidMove(int x, int y, int moveX, int moveY, taken currPlayer, bool isEating, board& g_board, bool checkRiskOnKing)
{
	taken currTaken = g_board.getTakenOfSquare(moveX, moveY);
	if (!isEating && currTaken == taken::EMPTY && (!checkRiskOnKing || checkRisksOnKing(x ,y , moveX, moveY, g_board)))
	{
		square sq = g_board.getSquare(moveX, moveY);
		s_listOfValidMoves.push_back(sq);
		return true;
	}
	else if (isEating && currPlayer != currTaken && currTaken != taken::EMPTY && (!checkRiskOnKing || checkRisksOnKing(x, y, moveX, moveY, g_board)))
	{
		square sq = g_board.getSquare(moveX, moveY);
		s_listOfValidMoves.push_back(sq);
		return false;
	}
	return false;
}

void pawn::printSoldier()
{
		cout << "P";
}
