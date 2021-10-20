#include "game.h"
#include "square.h"
game::game(typeGame currgame, int sizeBoard) :g_currGame(currgame),g_winner(winner::NO_ONE), g_statusGame(statusGame::NOT_OVER), g_currTurn(currTurn::PLAYER1T), g_board((int)currgame, sizeBoard) {}
game::game(typeGame& f_currgame, winner f_winner, statusGame f_statusGame, currTurn f_currTurn , istream& inFile): g_board(inFile)
{
	g_currGame = f_currgame;
	g_winner = f_winner;
	g_statusGame = f_statusGame;
	g_currTurn = f_currTurn;
}
game::game(const game& other):g_board(other.g_board)
{
	g_winner = other.g_winner;
	g_currTurn = g_currTurn;
	g_listOfValidMove = other.g_listOfValidMove;
	g_risks = other.g_risks;
}

game::game(game&& other) : g_board(move(other.g_board))
{
	g_winner = other.g_winner;
	g_currTurn = g_currTurn;
	g_listOfValidMove = other.g_listOfValidMove;
	g_risks = other.g_risks;
}
void game::checkValidMoveOfSoldier(int x, int y)
{
	if (!g_board.checkIfBound(x - 1, y - 1))
		throw invalid_argument("Location not in bound!");
	soldier* sol = g_board.getSoldier(x - 1, y - 1);
	if (sol == nullptr)
		throw invalid_argument("You must choose square with soldier!");
	sol->checkValidMove(x, y, g_board, true);
	if (sol->getListOfValidMove().empty())
		throw invalid_argument("There is no valid moves");
	g_listOfValidMove = sol->getListOfValidMove();
	sol->freeListOfValidMoves();
}
//--------------------------------------------------------------------------------------------------------------------//
const game& game::operator=(const game& other)
{
	if (this != &other)
	{
		g_board = other.g_board;
		g_winner = other.g_winner;
		g_currTurn = g_currTurn;
		g_listOfValidMove = other.g_listOfValidMove;
		g_risks = other.g_risks;
	}
	return *this;
}
//--------------------------------------------------------------------------------------------------------------------//
const game& game::operator=(game&& other)
{
	if (this != &other)
	{
		g_board = move(other.g_board);
		g_winner = other.g_winner;
		g_currTurn = g_currTurn;
		g_listOfValidMove = other.g_listOfValidMove;
		g_risks = other.g_risks;
	}
	return *this;
}
//---------------------------------------------------------------------------------------------------------------//
void game::updateTurn()
{
	if (g_currTurn == currTurn::PLAYER1T) 
		g_currTurn = currTurn::PLAYER2T;
	else
		g_currTurn = currTurn::PLAYER1T;
}
//--------------------------------------------------------------------------------------------------------------------//
bool game::checkIfMyTurn(int fromX, int fromY)
{
	if (g_board.getTakenOfSquare(fromX, fromY) == taken::FULL1 && g_currTurn == currTurn::PLAYER1T)
		return true;
	if (g_board.getTakenOfSquare(fromX, fromY) == taken::FULL2 && g_currTurn == currTurn::PLAYER2T)
		return true;
	return false;
}
//----------------------------------------------------------------------------------------------------------------------//
void game::printValidMove()const
{
	printList(g_listOfValidMove);

}
//----------------------------------------------------------------------------------------------------------------------//
void game::printRisks() const
{
	printList(g_risks);
}
//-----------------------------------------------------------------------------------------------------------------------------//
void game::freeListOfValidMove()
{
	g_listOfValidMove.clear();
}
//-------------------------------------------------------------------------------------------------//
void game::freeListOfRisks()
{
	g_risks.clear();
}
//-------------------------------------------------------------------------------------------------//
void game::printBoardAndDetailsOnTheGame()
{
	if (g_statusGame == statusGame::OVER)
	{
		cout << "The game is over!\n";
		if (g_winner == winner::PLAYER1WIN)
			cout << "The winner is: player 1 \n";
		else
			cout << "The winner is: player 2 \n";
	}
	else
	{
		cout << "The game in progress.\n";
		if (g_currTurn == currTurn::PLAYER1T)
			cout << "Player1's turn (WHITE soldiers).\n";
		else
			cout << "Player2's turn (RED soldiers).\n";

	}

	cout << g_board;

}
//-------------------------------------------------------------------------------------------------//
const statusGame& game::getStatusOfGame() const
{
	return g_statusGame;
}
//-------------------------------------------------------------------------------------------------//
const taken& game::getTaken(int x, int y)const
{
	return g_board.getTakenOfSquare(x, y);
}
//-------------------------------------------------------------------------------------------------//
const isValid& game::getIsValid(int x, int y) const
{
	return g_board.getStatusOfSquare(x, y);
}
//----------------------------------------------------------------------------------------------------------------------//
int game::getSizeOfBoard() const
{
	return g_board.getSizeOfBoard();
}

void game::save(ostream& out)
{
	out.write(rcastc(&g_currGame), sizeof(g_currGame));
	out.write(rcastc(&g_winner), sizeof(g_winner));
	out.write(rcastc(&g_statusGame), sizeof(g_statusGame));
	out.write(rcastc(&g_currTurn), sizeof(g_currTurn));
	if (!out.good())
		throw invalid_argument("The save failed.");
	g_board.save(out);
}

void game::printList(const list<square>& lst) const 
{
	if (lst.size() == 0)
		cout << "The list is empty\n";
	else
	{
		int counter = 1;
		for (auto& currVlaue : lst)
		{
			int* location = currVlaue.getLocation();
			cout << counter << ". " << location[0] + 1 << " " << location[1] + 1 << endl;
		}
	}
}

