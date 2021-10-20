#include "chess.h"
#include "board.h"
chess::chess(typeGame type, int sizeBoard) : game(type, sizeBoard){}

void chess::checkRisks(int x, int y)
{
	if (!g_board.checkIfBound(x - 1, y - 1))
		throw invalid_argument("Location not in bound!");
	soldier* sol = g_board.getSoldier(x - 1, y - 1);
	if (sol == nullptr)
		throw invalid_argument("You must choose square with soldier.");
	g_board.findRisks(x - 1,y - 1);
	if (sol->getListOfRisks().empty())
		throw invalid_argument("Soldier not in risk");
	g_risks = sol->getListOfRisks();
	sol->freeListOfRisks();
}
////-------------------------------------------------------------------------------------------------------------//
/*This function make a movment, we get location from where to go and loction where to go.*/
bool chess::gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier)
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
		if (iter != solList.end())
		{
			g_board.updateBoard(fromX - 1, fromY - 1, toX - 1, toY - 1);
			if (typeid(*sol).name() == typeid(pawn).name() && (toX == g_board.getSizeOfBoard() || toX == 1))
				g_board.upgradePawnToQueen(sol);
			checkIfTheNotOver();
			updateTurn(); //after movment update the turn.
			valid = true;
		}
		else
			throw invalid_argument("This is not a valid move.");
	}
	else 
		throw invalid_argument("Its not your soldier.");

	return valid;
}
//-------------------------------------------------------------------------------------------------------------------------//
/*This function check if there is valid moves on the board, if not the game is over.*/
bool chess::checkIfTheNotOver()
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
//----------------------------------------------------------------------------------------------------------------------//
bool chess::checkIfBound(int ind1, int ind2) const
{
	int size = g_board.getSizeOfBoard();
	if (ind1 >= 0 && ind1 <= size - 1 && ind2 >= 0 && ind2 <= size - 1)
		return true;
	return false;
}
//----------------------------------------------------------------------------------------------------------------------//
void chess::printName()
{
	cout << "Chess Game";
}

