#include "amazonas.h"
#include "game.h"
#include "board.h"
#include "queenOfAmazonas.h"
#include <algorithm>

amazonas::amazonas(typeGame type, int sizeBoard) : game(type, sizeBoard)
{
}
//------------------------------------------------------------------------------------------------------//
bool amazonas::gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier)
{
	bool valid = false;
	if (!g_board.checkIfBound(fromX - 1, fromY - 1))
		throw invalid_argument("Location not in bound!");
	if (!g_board.checkIfBound(toX - 1, toY - 1))
		throw invalid_argument("Location not in bound!");
	if (checkIfMyTurn(fromX - 1, fromY - 1)) // check the current turn
	{
		soldier* sol = g_board.getSoldier(fromX - 1, fromY - 1);
		if(g_board.getStatusOfSquare(toX - 1, toY - 1) == isValid::NOT_VALID)
			throw invalid_argument("The location that you want to move to is darted.");
		if (withSoldier)
		{
			sol->checkValidMove(fromX, fromY, g_board, withSoldier); // check valid move with queen and update the list.
			list<square> solList = sol->getListOfValidMove();
			list<square>::iterator iter;
			iter = find(solList.begin(), solList.end(), g_board.getSquare(toX - 1, toY - 1));
			if (iter != solList.end()) // this function find if there is the location (like the to) in the list
			{
				g_board.updateBoard(fromX - 1, fromY - 1, toX - 1, toY - 1, withSoldier); // after queen move
				valid = true;
				sol->freeListOfValidMoves();
			}
			else
			{
				sol->freeListOfValidMoves();
				throw invalid_argument("This is not valid move.");
			}

		}
		else
		{
			sol->checkValidMove(fromX, fromY, g_board, false);// create the list
			list<square> solList = sol->getListOfRisks();
			list<square>::iterator iter;
			iter = find(solList.begin(), solList.end(), g_board.getSquare(toX - 1, toY - 1));
			if (iter != solList.end())
			{
				valid = true;
				g_board.updateBoard(fromX - 1, fromY - 1, toX - 1, toY - 1, false); // to dart
				checkIfTheNotOver();
				updateTurn(); //after movment update the turn.
			}
			else
			{
				sol->freeListOfValidMoves();
				throw invalid_argument("This is not valid move.");
			}
			sol->freeListOfRisks();

		}
	}
	else
		throw invalid_argument("Its not your soldier.");
	return valid;
}
//------------------------------------------------------------------------------------------//
void amazonas::checkRisks(int x, int y)
{
	if (g_board.getTakenOfSquare(x - 1, y - 1) == taken::EMPTY && g_board.getStatusOfSquare(x - 1, y - 1) == isValid::VALID)
	{
		soldier* dart = new queenOfAmazonas();
		dart->checkValidMove(x, y, g_board, false);
		g_risks = dart->getListOfRisks();
		dart->freeListOfRisks();
		delete dart;
	}
}
//This function check valid moves in the oppsite player before update turn.
bool amazonas::checkIfTheNotOver()
{
	bool foundValidMove = false;
	bool player1ValidMoves = g_board.checkValidMovesInArr(taken::FULL1, g_board);
	bool player2ValidMoves = g_board.checkValidMovesInArr(taken::FULL2, g_board);
	if (player1ValidMoves && player2ValidMoves)
		foundValidMove = true;
	
	if (foundValidMove == false)
	{
		g_statusGame = statusGame::OVER;
		if (player1ValidMoves)
			g_winner = winner::PLAYER1WIN;
		else
			g_winner = winner::PLAYER2WIN;
		
	}
	return foundValidMove;
}

void amazonas::printName()
{
	cout << "Game Of The Amazonas";
}
