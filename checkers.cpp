#include "checkers.h"
#include "chess.h"
#include <string>
checkers::checkers(typeGame type, int sizeBoard): game(type, sizeBoard)
{}

void checkers::checkRisks(int x, int y)
{
	int ind1 = x - 1, ind2 = y - 1;
	if (!g_board.checkIfBound(ind1, ind2))
		throw invalid_argument("Location not in bound!");
	if (g_board.getStatusOfSquare(ind1, ind2) == isValid::NOT_VALID)
		throw invalid_argument("Location is not valid!");
	if(g_board.getTakenOfSquare(ind1, ind2) == taken::EMPTY)
		throw invalid_argument("Location is empty!");
	int tmp = 1;
	if (g_board.getTakenOfSquare(ind1, ind2) == taken::FULL1)
	{
		possibleRisks(ind1, ind2, direction::DOWNRIGHT, taken::FULL2);
		possibleRisks(ind1, ind2, direction::DOWNLEFT, taken::FULL2);
		possibleRisks(ind1, ind2, direction::UPRIGHT, taken::FULL2);
		possibleRisks(ind1, ind2, direction::UPLEFT, taken::FULL2);
	}
	else  // FULL2
	{
		possibleRisks(ind1, ind2, direction::DOWNRIGHT, taken::FULL1);
		possibleRisks(ind1, ind2, direction::DOWNLEFT, taken::FULL1);
		possibleRisks(ind1, ind2, direction::UPRIGHT, taken::FULL1);
		possibleRisks(ind1, ind2, direction::UPLEFT, taken::FULL1);
	}
	if (g_board.getSoldier(ind1, ind2)->getListOfRisks().empty())
		throw "There are no risks!";	
}
//-------------------------------------------------------------------------------------------------------------//
void checkers::possibleRisks(int x, int y, direction dir, taken opPlayer)
{
	int tmp = 1;
	bool found = false;
	switch (dir)
	{
	case direction::UPLEFT:
		while (g_board.checkIfBound(x - tmp, y - tmp) && found == false)
		{
			if (tmp == 1 && opPlayer == taken::FULL1 && g_board.getTakenOfSquare(x - tmp, y - tmp) == taken::FULL1 && emptyBehind(x + 1, y + 1))
			{
				g_risks.push_back(g_board.getSquare(x - tmp, y - tmp));
				found = true;
			}
			else if (g_board.getTakenOfSquare(x - tmp, y - tmp) != opPlayer && g_board.getTakenOfSquare(x - tmp, y - tmp) != taken::EMPTY)
			{
				found = true;
			}
			else if (g_board.getTakenOfSquare(x - tmp, y - tmp) == opPlayer)
			{
				if (emptyBehind(x + 1, y + 1) && typeid(*(g_board.getSoldier(x - tmp, y - tmp))).name() == typeid(checkersKing).name())
				{
					g_risks.push_back(g_board.getSquare(x - tmp, y - tmp));
					found = true;
				}

			}

			tmp++;
		}
		break;

	case direction::UPRIGHT:
		while (g_board.checkIfBound(x - tmp, y + tmp) && found == false)
		{
			if (tmp == 1 && opPlayer == taken::FULL1 && g_board.getTakenOfSquare(x - tmp, y + tmp) == taken::FULL1 && emptyBehind(x + 1, y - 1))
			{
				g_risks.push_back(g_board.getSquare(x - tmp, y + tmp));
				found = true;
			}
			else if (g_board.getTakenOfSquare(x - tmp, y + tmp) != opPlayer && g_board.getTakenOfSquare(x - tmp, y + tmp) != taken::EMPTY)
			{
				found = true;
			}
			else if (g_board.getTakenOfSquare(x - tmp, y + tmp) == opPlayer)
			{
				if (emptyBehind(x + 1, y - 1) && typeid(*(g_board.getSoldier(x - tmp, y + tmp))).name() == typeid(checkersKing).name())
				{
					g_risks.push_back(g_board.getSquare(x - tmp, y + tmp));
					found = true;
				}
			}
			tmp++;
		}
		break;

	case direction::DOWNLEFT:
		while (g_board.checkIfBound(x + tmp, y - tmp) && found == false)
		{
			if (tmp == 1 && opPlayer == taken::FULL2 && g_board.getTakenOfSquare(x + tmp, y - tmp) == taken::FULL2 && emptyBehind(x - 1, y + 1))
			{
				g_risks.push_back(g_board.getSquare(x + tmp, y - tmp));
				found = true;
			}
			else if (g_board.getTakenOfSquare(x + tmp, y - tmp) != opPlayer && g_board.getTakenOfSquare(x + tmp, y - tmp) != taken::EMPTY)
			{
				found = true;
			}
			else if (g_board.getTakenOfSquare(x + tmp, y - tmp) == opPlayer)
			{
				if (emptyBehind(x - 1, y + 1) && typeid(*(g_board.getSoldier(x + tmp, y - tmp))).name() == typeid(checkersKing).name())
				{
					g_risks.push_back(g_board.getSquare(x + tmp, y - tmp));
					found = true;
				}
			}
			tmp++;
		}
		break;

	case direction::DOWNRIGHT:
		while (g_board.checkIfBound(x + tmp, y + tmp) && found == false)
		{
			if (tmp == 1 && opPlayer == taken::FULL2 && g_board.getTakenOfSquare(x + tmp, y + tmp) == taken::FULL2 && emptyBehind(x - 1, y - 1))
			{
				g_risks.push_back(g_board.getSquare(x + tmp, y + tmp));
				found = true;
			}
			else if (g_board.getTakenOfSquare(x + tmp, y + tmp) != opPlayer && g_board.getTakenOfSquare(x + tmp, y + tmp) != taken::EMPTY)
			{
				found = true;
			}
			else if (g_board.getTakenOfSquare(x + tmp, y + tmp) == opPlayer)
			{
				if (emptyBehind(x - 1, y - 1) && typeid(*(g_board.getSoldier(x + tmp, y + tmp))).name() == typeid(checkersKing).name())
				{
					g_risks.push_back(g_board.getSquare(x + tmp, y + tmp));
					found = true;
				}
			}
			tmp++;
		}
		break;
	}
}
//This function check if the square empty behind.
bool checkers::emptyBehind(int x, int y)
{
	if (g_board.checkIfBound(x,y))
	{
		if (g_board.getTakenOfSquare(x, y) == taken::EMPTY)
			return true;
	}
	return false;
}
/*The function for moves.*/
bool checkers::gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier)
{
	bool valid = false;
	if (!g_board.checkIfBound(fromX - 1, fromY - 1))
		throw invalid_argument("Location not in bound!");
	if (!g_board.checkIfBound(toX - 1, toY - 1))
		throw invalid_argument("Location not in bound!");
	if (checkIfMyTurn(fromX - 1, fromY - 1)) // check the current turn
	{
		soldier* sol = g_board.getSoldier(fromX - 1, fromY - 1);
		if (sol == nullptr)
			throw invalid_argument("The location is Empty.");
		sol->checkValidMove(fromX, fromY, g_board, true);
		list<square> solList = sol->getListOfValidMove();
		list<square>::iterator iter;
		iter = find(solList.begin(), solList.end(), g_board.getSquare(toX - 1, toY - 1));
		if (iter != solList.end()) // this function find if ther is the location (like the to) in the list
		{
			direction curDir = whatDirection(fromX, fromY, toX,toY);
			valid = true;
			sol->freeListOfValidMoves();
			g_board.updateBoard(fromX - 1, fromY - 1, toX - 1, toY - 1, curDir); //WORK WITH INDEX and players
			if (typeid(*sol).name() == typeid(checkersSoldier).name() && (toX == 8 || toX == 1))
				g_board.upgradeSoldierToKing(sol);
			checkIfTheNotOver();
			//after movment update the turn
			updateTurn();
		}
		else
			throw invalid_argument("This is not a valid move.");
	}
	else
		throw invalid_argument("Its not your soldier.");
	//g_board.getTakenOfSquare(0, 0);

	return valid;

}

const direction& checkers::whatDirection(int fromX, int fromY, int toX, int toY)
{
	int directionX = fromX - toX, directionY = fromY - toY;
	if (directionX > 0 && directionY < 0) //up right
		return direction::UPRIGHT;
	else if (directionX > 0 && directionY > 0) // up left
		return direction::UPLEFT;
	else if (directionX < 0 && directionY < 0) // down left
		return direction::DOWNLEFT;
	else if (directionX < 0 && directionY > 0) // down right
		return direction::DOWNRIGHT;
}

bool checkers::checkIfTheNotOver()
{
	bool foundValidMove = false;
	if (g_currTurn == currTurn::PLAYER1T)
	{
		if (g_board.checkValidMovesInArr(taken::FULL2, g_board))
			foundValidMove = true;
	}
	else if (g_currTurn == currTurn::PLAYER2T)
	{
		if (g_board.checkValidMovesInArr(taken::FULL1, g_board))
			foundValidMove = true;
	}

	if (foundValidMove == false)
	{
		g_statusGame = statusGame::OVER;
		if (g_currTurn == currTurn::PLAYER1T)
			g_winner = winner::PLAYER1WIN;
		else
			g_winner = winner::PLAYER2WIN;
		return true;
	}
	return foundValidMove;
}

void checkers::printName()
{
	cout << "Checkers Game";
}
