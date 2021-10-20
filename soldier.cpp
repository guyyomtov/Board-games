#include "soldier.h"
#include "board.h"
soldier::soldier(){}
soldier::soldier(const square& sq):s_square(sq)
{
}
soldier::soldier(const soldier& other) 
{
	*this = other;
}
soldier::soldier(soldier&& other) 
{
	*this = move(other);
}
const soldier& soldier::operator=(const soldier& other)
{
	if (this != &other)
	{
		this->s_listOfValidMoves = other.s_listOfValidMoves;
		this->s_listOfRisks = other.s_listOfRisks;
		this->s_square = other.s_square;
	}
	return *this;
}
const soldier& soldier::operator=(soldier&& other)
{
	if (this != &other)
	{
		this->s_listOfValidMoves = other.s_listOfValidMoves;
		this->s_listOfRisks = other.s_listOfRisks;
		this->s_square = other.s_square;
	}
	return *this;
} 


const square& soldier::getSquare() const
{
	return s_square;
}

void soldier::setSquare(const square& sq)
{
	s_square = sq;
}

//------------------------------------------------------------------------------------------------------------------------------//
//same functions for queen, bishop, rook in chess.
void soldier::checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing)
{
	int move = 1;
	bool stopped = false;
	taken currPlayer = g_board.getTakenOfSquare(x, y);
	switch (currDir)
	{
	case direction::DOWNRIGHT:
	{
		while (g_board.checkIfBound(x + move, y + move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x + move, y + move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::DOWNLEFT:
	{
		while (g_board.checkIfBound(x + move, y - move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x + move, y - move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}

		break;
	}
	case direction::UPRIGHT:
	{
		while (g_board.checkIfBound(x - move, y + move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x - move, y + move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::UPLEFT:
	{
		while (g_board.checkIfBound(x - move, y - move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x - move, y - move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::UP:
	{
		while (g_board.checkIfBound(x - move, y) && !stopped)
		{
			if (!checkIfValidMove(x, y, x - move, y, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::LEFT:
	{
		while (g_board.checkIfBound(x, y - move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x, y - move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::DOWN:
	{
		while (g_board.checkIfBound(x + move, y) && !stopped)
		{
			if (!checkIfValidMove(x, y, x + move, y, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}
	case direction::RIGHT:
	{
		while (g_board.checkIfBound(x, y + move) && !stopped)
		{
			if (!checkIfValidMove(x, y, x, y + move, currPlayer, g_board, checkRiskOnKing))
				stopped = true;
			move++;
		}
		break;
	}

	}
}
bool soldier::checkIfValidMove(int x, int y, int moveX, int moveY, taken currPlayer, board& g_board, bool checkRiskOnKing)
{
	if (g_board.getTakenOfSquare(moveX, moveY) == taken::EMPTY && (!checkRiskOnKing || checkRisksOnKing(x, y, moveX, moveY, g_board)))
	{
		s_listOfValidMoves.push_back(g_board.getSquare(moveX, moveY));
		return true;
	}
	else if (currPlayer != g_board.getTakenOfSquare(moveX, moveY) && (!checkRiskOnKing || checkRisksOnKing(x, y, moveX, moveY, g_board)))
	{
		s_listOfValidMoves.push_back(g_board.getSquare(moveX, moveY));
		return false;
	}
	return false;
}

void soldier::printValidMoves() const
{
	if(s_listOfValidMoves.size() == 0)
		cout << "The list is empty\n";
	else
	{
		int counter = 1;
		for (auto& currVlaue : s_listOfValidMoves)
		{
			int* location = currVlaue.getLocation();
			cout << counter << ". " << location[0] << " " << location[1] << endl;
		}
	}
}

list<square>& soldier::getListOfValidMove() 
{
	return s_listOfValidMoves;
}

list<square>& soldier::getListOfRisks()
{
	return s_listOfRisks;
}

//bool soldier::isExists(const square& sq, const list<square>& lst)
//{
//	for (auto& currValue : lst)
//	{
//		if (currValue == sq)
//			return true;
//	}
//	return false;
//}

void soldier::updateList(const square& sq)
{
	s_listOfRisks.push_back(sq);
}
//in every movment in chess we check if ther is risks on the king of th player and if ther is the movment nor valid!
bool soldier::checkRisksOnKing(int x, int y, int moveX, int moveY, board& g_board)
{
	bool eaten = false;
	eaten = g_board.updateBoard(x, y, moveX, moveY);
	soldier* king = g_board.getKingFromPlayer(g_board.getTakenOfSquare(moveX, moveY));
	square sqKing = king->getSquare();
	int* locaion = sqKing.getLocation(); 
	g_board.findRisks(locaion[0], locaion[1]); // location of king
	if (king->getListOfRisks().empty()) // check risks on king
	{
		g_board.undoUpdateBoard(x, y, moveX, moveY, eaten);
		return true;
	}
	else
	{
		g_board.undoUpdateBoard(x, y, moveX, moveY,eaten);
		king->freeListOfRisks();
		return false;
	}
}

void soldier::freeListOfValidMoves()
{
	s_listOfValidMoves.clear();
}

void soldier::freeListOfRisks()
{
	s_listOfRisks.clear();
}
