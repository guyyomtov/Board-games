#include "queenOfAmazonas.h"
#include "soldier.h"
#include "game.h"
#include "board.h"
void queenOfAmazonas::checkValidMove(int x, int y, board& g_board ,bool withSoldier)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (g_board.checkIfBound(ind1, ind2))
	{
		checkPossibleMove(ind1, ind2, direction::DOWNRIGHT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::DOWNLEFT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::UPRIGHT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::UPLEFT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::DOWN, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::RIGHT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::LEFT, withSoldier, g_board);
		checkPossibleMove(ind1, ind2, direction::UP, withSoldier, g_board);
	}
}

bool queenOfAmazonas::checkIfValidMove(int x, int y, bool withSoldier, board& g_board)
{
	if (g_board.getStatusOfSquare(x, y) == isValid::VALID && g_board.getTakenOfSquare(x, y) == taken::EMPTY)
	{
		if (withSoldier)
			s_listOfValidMoves.push_back(g_board.getSquare(x, y));
		else
			s_listOfRisks.push_back(g_board.getSquare(x, y));

		return true;
	}

	return false;
}
//This function check the queen moves in 8 different directions on the board.
//Its not duplicate code because any case is differnt direction!
void queenOfAmazonas::checkPossibleMove(int x, int y, direction currDir, bool withSoldier, board& g_board)
{
	int move = 1;
	bool stopped = false;

	switch (currDir)
	{
	case direction::DOWNRIGHT:
	{
		while (g_board.checkIfBound(x + move, y + move) && !stopped)
		{
			if (!checkIfValidMove(x + move, y + move, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::DOWNLEFT:
	{
		while (g_board.checkIfBound(x + move, y - move) && !stopped)
		{
			if (!checkIfValidMove(x + move, y - move, withSoldier, g_board))
				stopped = true;
			move++;
		}

		break;
	}
	case direction::UPRIGHT:
	{
		while (g_board.checkIfBound(x - move, y + move) && !stopped)
		{
			if (!checkIfValidMove(x - move, y + move, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::UPLEFT:
	{
		while (g_board.checkIfBound(x - move, y - move) && !stopped)
		{
			if (!checkIfValidMove(x - move, y - move, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::UP:
	{
		while (g_board.checkIfBound(x - move, y) && !stopped)
		{
			if (!checkIfValidMove(x - move, y, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::LEFT:
	{
		while (g_board.checkIfBound(x, y - move) && !stopped)
		{
			if (!checkIfValidMove(x, y - move, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::DOWN:
	{
		while (g_board.checkIfBound(x + move, y) && !stopped)
		{
			if (!checkIfValidMove(x + move, y, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::RIGHT:
	{
		while (g_board.checkIfBound(x, y + move) && !stopped)
		{
			if (!checkIfValidMove(x, y + move, withSoldier, g_board))
				stopped = true;
			move++;
		}
		break;
	}

	}
}

void queenOfAmazonas::printSoldier()
{
	cout << "Q";
}
