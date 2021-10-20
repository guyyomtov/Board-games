#include "player.h"
#include "soldier.h"
//every player have array of pointer to soldier and in chess have pointer to the king of the player.
player::player(taken curr ,int size) : SoldiersPlayer(size), theKing(nullptr) {} //default ctor 

player::player(const player& other) :SoldiersPlayer(other.SoldiersPlayer), theKing(other.theKing), curr(other.curr), countEatenSol(other.countEatenSol)
{
}

player::player(player&& other) : SoldiersPlayer(move(other.SoldiersPlayer)), theKing(other.theKing), curr(other.curr), countEatenSol(other.countEatenSol)
{
}

player::~player()
{

}
const player& player::operator=(const player& other)
{
	if (this != &other)
	{
		SoldiersPlayer = other.SoldiersPlayer;
		theKing = other.theKing;
		curr = other.curr;
		countEatenSol = other.countEatenSol;
	}
	return *this;
}
const player& player::operator=(player&& other)
{
	if (this != &other)
	{
		SoldiersPlayer = move(other.SoldiersPlayer);
		theKing = other.theKing;
		curr = other.curr;
		countEatenSol = other.countEatenSol;
	}
	return *this;
}
void player::freeArrayOfPointer()
{
	int size = SoldiersPlayer.size();
	for (int i = 0;i < size;i++)
	{
		delete SoldiersPlayer[i];
	}
	//SoldiersPlayer to delete?? 
}
void player::setSoldierInArr(soldier* p1)
{
	SoldiersPlayer.push_back(p1);
}
vector<soldier*> player::getArrayOfSoldiers()const
{
	return SoldiersPlayer;
}
const int player::getSizeOfArr()const
{
	return SoldiersPlayer.size() - countEatenSol;
}
//This function check to every soldier's valid moves. 
void player::checkRisksInArr(soldier* sol, const square& sq, board& g_board)
{
	//int size = SoldiersPlayer.size() - countEatenSol;
	for (int i = 0;i < (SoldiersPlayer.size() - countEatenSol);i++)
	{
		int* currLocation = SoldiersPlayer[i]->getSquare().getLocation();
		SoldiersPlayer[i]->checkValidMove(currLocation[0] + 1, currLocation[1] + 1, g_board, false);
		list<square> solList = SoldiersPlayer[i]->getListOfValidMove();
		list<square>::iterator iter;
		iter = find(solList.begin(), solList.end(), sq);
		if (iter != solList.end())
			sol->updateList(SoldiersPlayer[i]->getSquare());
		SoldiersPlayer[i]->freeListOfValidMoves();
	}
}

void player::updateArr(soldier* eatenSol)
{
	int size = SoldiersPlayer.size() - countEatenSol;
	for (int i = 0;i < (SoldiersPlayer.size() - countEatenSol); i++)
	{
		if (SoldiersPlayer[i] == eatenSol)
		{
			soldier* tmp = SoldiersPlayer[i];
			SoldiersPlayer[i] = SoldiersPlayer[size - 1];
			SoldiersPlayer[size - 1] = tmp;
			++countEatenSol;
		}
	}
	
}

soldier* player::addSizeToArray()
{
	int size = SoldiersPlayer.size();
	--countEatenSol;
	return SoldiersPlayer[(size - countEatenSol) - 1];
}

bool player::checkValidmovesInArrOfSoldiers(board& g_board)
{
	int size = SoldiersPlayer.size() - countEatenSol;
	bool foundValidMove = false;
	for (int i = 0;i < (SoldiersPlayer.size() - countEatenSol) && !foundValidMove;i++)
	{
		square sq = SoldiersPlayer[i]->getSquare();
		int* location = sq.getLocation();
		//SoldiersPlayer[i]->freeListOfValidMoves();
		SoldiersPlayer[i]->checkValidMove(location[0] + 1, location[1] + 1, g_board, true);
	//	listOfSquares list = move(SoldiersPlayer[i]->getListOfValidMove()); 
		if (!SoldiersPlayer[i]->getListOfValidMove().empty())
			foundValidMove = true;
		SoldiersPlayer[i]->freeListOfValidMoves();
	}
	return foundValidMove;
}
void player::upgradeSoldier(soldier* Pawn, soldier* nQueen)
{
	int size = SoldiersPlayer.size() - countEatenSol;
	bool found = false;
	for (int i = 0 ;i < (SoldiersPlayer.size() - countEatenSol) && !found;i++)
	{
		if (SoldiersPlayer[i] == Pawn)
		{
			SoldiersPlayer[i] = nQueen;
			found = true;
		}
	}
}

void player::mallocArr(int size)
{
	SoldiersPlayer.reserve(size);
}
