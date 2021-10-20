#include "board.h"
#include "square.h"
#include "soldier.h"
#include "knight.h"
#include "game.h"
#include "queenOfAmazonas.h"
#include "checkersSoldier.h"
/*Every square in the board initilize to error/ valid square and full in player1/2 or empty/ darted.
and every square have a pointer to soldier if there is a soldier in the square or nullptr*/
//In this ctor we get the size of the board and which game the user want to play.
//accordinatliy to that we initialize the board.
board::board(int typeGame, int size) : player1(taken::FULL1), player2(taken::FULL2), sizeOfBoard(size)
{
	switch (typeGame)
	{
	case 1:
		initCheckers();
		break;
	case 2 :
		initAmazonas();
		break;
	case 3:
		initChess();
		break;
	}
}
board::board(istream& inFile):player1(taken::FULL1), player2(taken::FULL2)
{
	inFile.read(rcastc(&sizeOfBoard), sizeof(sizeOfBoard));
	if (!inFile.good())
		throw invalid_argument("The load failed.");
	Board.reserve(sizeOfBoard);
	for (int i = 0;i < sizeOfBoard;i++)
	{
		vector<square> tmpArr;
		tmpArr.reserve(sizeOfBoard);
		for (int j = 0;j < sizeOfBoard;j++)
		{
			square sq(inFile);
			if (sq.getTaken() != taken::EMPTY)
			{
				int len;
				char* type;
				inFile.read(rcastc(&len), sizeof(len));
				type = new char[len];
				inFile.read(rcastc(type), len);
				type[len] = '\0';
				if (!inFile.good())
					throw invalid_argument("The load failed.");
				soldier* sol = checkWhichSoldierToAllocate(type);
				if (sol == nullptr)
					throw bad_alloc();
				sq.setSoldier(sol);
				sol->setSquare(sq);
				if (sq.getTaken() == taken::FULL1)
					player1.setSoldierInArr(sol);
				else // full2
					player2.setSoldierInArr(sol);
			}
			tmpArr.push_back(sq);
		}
		Board.push_back(tmpArr);

	}
}
soldier* board::checkWhichSoldierToAllocate(char* type)
{
	if (strcmp(type, (typeid(pawn).name())) == 0)
		return new pawn();
	else if(strcmp(type, typeid(rook).name()) == 0)
		return new rook();
	else if (strcmp(type, typeid(bishop).name()) == 0)
		return new bishop();
	else if (strcmp(type, typeid(knight).name()) == 0)
		return new knight();
	else if (strcmp(type, typeid(queen).name()) == 0)
		return new queen();
	else if (strcmp(type, typeid(king).name()) == 0)
		return new king();
	else if (strcmp(type, typeid(checkersSoldier).name()) == 0)
		return new checkersSoldier();
	else if (strcmp(type, typeid(checkersKing).name()) == 0)
		return new checkersKing();
	else if (strcmp(type, typeid(queenOfAmazonas).name()) == 0)
		return new queenOfAmazonas();
	//cout << typeid(checkersSoldier).name() << " " << type << endl;
}
//This is initialize the chess's board.
void board::initChess()
{
	const int sizeOfChessSoldierArr = 16;
	player1.mallocArr(sizeOfChessSoldierArr); //create array of pointers to soldier to each player
	player2.mallocArr(sizeOfChessSoldierArr);
	Board.reserve(sizeOfBoard); //= new square * [sizeOfBoard];
	for (int i = 0;i < sizeOfBoard;i++)
	{
		vector<square> tmpVec;
		tmpVec.reserve(sizeOfBoard); //= new square[sizeOfBoard];
		soldier* Soldier = nullptr;
		for (int j = 0;j < sizeOfBoard;j++)
		{
			//Board[i][j] = square();
			square sqTmp;
			if (i == 0 || i == sizeOfBoard - 1)
			{
				if (j == 0 || j == 7)
					Soldier = new rook(); // polimorphizem
				else if (j == 1 || j == 6)
					Soldier = new knight();
				else if (j == 2 || j == 5)
					Soldier = new bishop();
				else if (j == 3)
					Soldier = new queen();
				else if (j == 4)
					Soldier = new king();

				if (Soldier == nullptr)
					throw bad_alloc();
			}
			else if (i == 1 || i == 6)
			{
				Soldier = new pawn();
				if (Soldier == nullptr)
					throw bad_alloc();
			}

			sqTmp.setLocation(i, j);
			sqTmp.setSoldier(Soldier);
			if (i == 0 || i == 1)
			{
				sqTmp.setTaken(taken::FULL1);
				Soldier->setSquare(sqTmp);
				player1.setSoldierInArr(Soldier);
				if (i == 0 && j == 4)
					player1.setKing(Soldier); // in the player we save the pointer to the king.
			}
			else if (i == 6 || i == sizeOfBoard - 1)
			{
				sqTmp.setTaken(taken::FULL2);
				Soldier->setSquare(sqTmp);
				player2.setSoldierInArr(Soldier);
				if (i == sizeOfBoard - 1 && j == 4)
					player2.setKing(Soldier);
			}
			else
				sqTmp.setTaken(taken::EMPTY);
			sqTmp.setValid(isValid::VALID);
			tmpVec.push_back(sqTmp);
		}
		Board.push_back(tmpVec);
	}
}
//This function initialize the amazonas board.
void board::initAmazonas()
{
	const int sizeOfAmazonasSoldierArr = 4;
	player1.mallocArr(sizeOfAmazonasSoldierArr); // create array of pointers to soldier to each player.
	player2.mallocArr(sizeOfAmazonasSoldierArr);
	Board.reserve(sizeOfBoard); //= new square* [sizeOfBoard];
	for (int i = 0;i < sizeOfBoard;i++)
	{
		vector<square> tmpVec;
		tmpVec.reserve(sizeOfBoard); //= new square[sizeOfBoard];
		for (int j = 0;j < sizeOfBoard;j++)
		{
			square squareTmp(i, j, nullptr);
			if ((i == 0 && (j == 3 || j == 6)) || (i == 3 && (j == 0 || j == 9))) // player1
			{
				squareTmp.setTaken(taken::FULL1);
				soldier* queenAmazon = new queenOfAmazonas();
				if (queenAmazon == nullptr)
					throw bad_alloc();
				squareTmp.setSoldier(queenAmazon);
				queenAmazon->setSquare(squareTmp);
				player1.setSoldierInArr(queenAmazon);

			}
			else if ((i == 9 && (j == 3 || j == 6)) || (i == 6 && (j == 0 || j == 9))) // player2 
			{
				squareTmp.setTaken(taken::FULL2);
				soldier* queenAmazon = new queenOfAmazonas();
				if (queenAmazon == nullptr)
					throw bad_alloc();
				squareTmp.setSoldier(queenAmazon);
				queenAmazon->setSquare(squareTmp);
				player2.setSoldierInArr(queenAmazon);
			}
			/*else
				Board[i][j] = squareTmp;*/
			tmpVec.push_back(squareTmp);
		}
		Board.push_back(tmpVec);
	}

}
//This function initialize the checkers's board.
void board::initCheckers()
{
	const int sizeOfCheckersSoldierArr = 12;
	player1.mallocArr(sizeOfCheckersSoldierArr); //create array of pointers to soldier to each player
	player2.mallocArr(sizeOfCheckersSoldierArr);
	Board.reserve(sizeOfBoard); //= new square * [sizeOfBoard];
	for (int i = 0;i < sizeOfBoard;i++)
	{
		vector<square> tmpVec;
		tmpVec.reserve(sizeOfBoard);
		for (int j = 0;j < sizeOfBoard;j++)
		{
			square sqTmp;
			sqTmp.setLocation(i, j);
			sqTmp.initStatusOfCheckers(i, j);
			if (sqTmp.getStatus() == isValid::VALID)
			{
				if (i <= 2) // player1
				{
					soldier* sol = new checkersSoldier();
					if (sol == nullptr)
						throw bad_alloc();
					sqTmp.setTaken(taken::FULL1);
					sol->setSquare(sqTmp);
					sqTmp.setSoldier(sol);
					player1.setSoldierInArr(sol);

				}
				else if (i >= 5) // player2
				{
					soldier* sol = new checkersSoldier();
					if (sol == nullptr)
						throw bad_alloc();
					sqTmp.setTaken(taken::FULL2);
					sol->setSquare(sqTmp);
					sqTmp.setSoldier(sol);
					player2.setSoldierInArr(sol);
				}
				else
					sqTmp.setTaken(taken::EMPTY);
			}
			else
				sqTmp.setTaken(taken::EMPTY);
			tmpVec.push_back(sqTmp);
		}
		Board.push_back(tmpVec);
	}

}

//----------------------------------------------------------------------------------------------------------------------------//
board::board(const board& other) :player1(other.player1), player2(other.player2),sizeOfBoard(other.sizeOfBoard)
{
	freeBoard();
	Board = other.Board;
}
//----------------------------------------------------------------------------------------------------------------------------//
board::board(board&& other):player1(move(other.player1)), player2(move(other.player2)), sizeOfBoard(other.sizeOfBoard)
{
	freeBoard();
	Board = move(other.Board);
	other.sizeOfBoard = 0;
}
//----------------------------------------------------------------------------------------------------------------------------//
board::~board() 
{
	freeBoard();
};
//----------------------------------------------------------------------------------------------------------------------------//
const isValid& board::getStatusOfSquare(int x, int y) const
{
	return Board[x][y].getStatus();
}
//----------------------------------------------------------------------------------------------------------------------------//
const taken& board::getTakenOfSquare(int x, int y) const
{
	return Board[x][y].getTaken();
}
//----------------------------------------------------------------------------------------------------------------------------//
const square& board::getSquare(int x, int y)const
{
	return Board[x][y];
}
//------------------------------------------------------------------------------------------------------------------------------//
void board::freeBoard()
{
	for (int i = 0;i < sizeOfBoard;i++)
	{
		Board[i].clear();
	}
	Board.clear();
}
/*After move this function update the board and the array of the players.*/
//this function update board after chess movment.
bool board::updateBoard(int fromX, int fromY, int toX, int toY)
{
	bool eaten = false;
	taken currPlayer = Board[fromX][fromY].getTaken();
	taken tmp = Board[toX][toY].getTaken();
	if (tmp != taken::EMPTY) // eating
	{
		soldier* eatenSol = Board[toX][toY].getSoldierFromSquare();
		if (currPlayer == taken::FULL1)
			player2.updateArr(eatenSol);
		else
			player1.updateArr(eatenSol);

		Board[toX][toY].setSoldier(nullptr);
		eaten = true;
	}
	soldier* sol = Board[fromX][fromY].getSoldierFromSquare();
	Board[fromX][fromY].setTaken(taken::EMPTY);
	Board[toX][toY].setTaken(currPlayer);
	sol->setSquare(Board[toX][toY]);
	Board[toX][toY].setSoldier(sol);
	Board[fromX][fromY].setSoldier(nullptr);
	return eaten;
}
//----------------------------------------------------------------------------------------------------------------------------//
//this function update board after amazonas movment.
void board::updateBoard(int fromX, int fromY, int toX, int toY,  bool queenMove)
{
	if (queenMove)
	{
		soldier* sol = Board[fromX][fromY].getSoldierFromSquare();
		taken tmp = Board[fromX][fromY].getTaken();
		Board[fromX][fromY].setTaken(taken::EMPTY);
		Board[fromX][fromY].setSoldier(nullptr);
		Board[toX][toY].setSoldier(sol);
		Board[toX][toY].setTaken(tmp);
		sol->setSquare(Board[toX][toY]);
	}
	else // dart move
	{
		Board[toX][toY].setValid(isValid::NOT_VALID); // in this case its the dart!
	}

}
//This function update board after checkers movment.
void board::updateBoard(int fromX, int fromY, int toX, int toY, direction curDir)
{
	int directionX = fromX - toX, directionY = fromY - toY;
	taken tmp = Board[fromX][fromY].getTaken();
	soldier* sol = Board[fromX][fromY].getSoldierFromSquare();
	//update taken of board
	Board[fromX][fromY].setTaken(taken::EMPTY);
	Board[fromX][fromY].setSoldier(nullptr);
	if (directionX == 1 || directionX == -1) // DOESNT EAT
	{
		Board[toX][toY].setTaken(tmp); // to update the board
	}
	else
	{
		Board[toX][toY].setTaken(tmp); // for sure valid move!
		if (curDir == direction::UPRIGHT) //up right
		{
			checkIfEatOrRegularMove(toX + 1, toY - 1, tmp);
		}
		else if (curDir == direction::UPLEFT) // up left
		{
			checkIfEatOrRegularMove(toX + 1, toY + 1, tmp);
		}
		else if (curDir == direction::DOWNLEFT) // down left
		{
			checkIfEatOrRegularMove(toX - 1, toY - 1, tmp);
		}
		else if (curDir == direction::DOWNRIGHT) // down right
		{
			checkIfEatOrRegularMove(toX - 1, toY + 1, tmp);
		}
	}
	sol->setSquare(Board[toX][toY]);
	Board[toX][toY].setSoldier(sol);

}
void board::checkIfEatOrRegularMove(int crossX, int crossY, taken currPlayer)
{
	if (Board[crossX][crossY].getTaken() == taken::EMPTY)
		return;
	else if (currPlayer == taken::FULL1) // if the cross not empty its must be on of the oppsite player
		player2.updateArr(Board[crossX][crossY].getSoldierFromSquare());
	else if (currPlayer == taken::FULL2)
		player1.updateArr(Board[crossX][crossY].getSoldierFromSquare());

	Board[crossX][crossY].setTaken(taken::EMPTY);
	Board[crossX][crossY].setSoldier(nullptr);

}
//----------------------------------------------------------------------------------------------------------------------------//
bool board::checkValidMovesInArr(taken currPlayer, board& g_board) 
{
	if (currPlayer == taken::FULL1)
		return player1.checkValidmovesInArrOfSoldiers(g_board);
	else
		return player2.checkValidmovesInArrOfSoldiers(g_board);
}
//----------------------------------------------------------------------------------------------------------------------------//
const board& board::operator=(board&& other)
{
	if (this != &other)
	{
		Board = move(other.Board);
		sizeOfBoard = other.sizeOfBoard;
		player1 = move(other.player1);
		player2 = move(other.player2);
		other.sizeOfBoard = 0;
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------------//
const board& board::operator=(const board& other)
{
	for (int i = 0;i < sizeOfBoard;i++)
		for (int j = 0;j < sizeOfBoard;j++)
			Board[i][j] = other.Board[i][j];
	player1 = other.player1;
	player2 = other.player2;
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------------//
soldier* board::getSoldier(int x, int y) const
{
	return Board[x][y].getSoldierFromSquare();
}
//----------------------------------------------------------------------------------------------------------------------------//
void board::findRisks(int ind1, int ind2)
{
	taken currPlayer = Board[ind1][ind2].getTaken();
	soldier* sol = Board[ind1][ind2].getSoldierFromSquare();
	square sq = Board[ind1][ind2];
	if (currPlayer == taken::FULL1)
		player2.checkRisksInArr(sol, sq, *this);
	else
		player1.checkRisksInArr(sol, sq, *this);
}
//----------------------------------------------------------------------------------------------------------------------------//
soldier* board::getKingFromPlayer(taken currPlayer)
{
	if (currPlayer == taken::FULL1)
		return player1.getKing();
	else
		return player2.getKing();
}
//----------------------------------------------------------------------------------------------------------------------------//
//For checking valid move in chess we make a valid move and update the board to check if ther is risks 
//on the king and the we undo the update board.(because we just want to check if ther is valid moves.)
void board::undoUpdateBoard(int fromX, int fromY, int toX, int toY, bool eaten)
{
	if (!eaten)
	{
		updateBoard(toX, toY, fromX, fromY);
	}
	else
	{
		soldier* solBackToLife, *currSoldier;
		currSoldier = Board[toX][toY].getSoldierFromSquare();
		taken currPlayer = getTakenOfSquare(toX, toY);
		if (currPlayer == taken::FULL1)
		{
			solBackToLife = player2.addSizeToArray();
			Board[toX][toY].setTaken(taken::FULL2);
		}
		else
		{
			solBackToLife = player1.addSizeToArray();
			Board[toX][toY].setTaken(taken::FULL1);
		}
		Board[fromX][fromY].setTaken(currPlayer);
		currSoldier->setSquare(Board[fromX][fromY]);
		Board[fromX][fromY].setSoldier(currSoldier);
		solBackToLife->setSquare(Board[toX][toY]);
		Board[toX][toY].setSoldier(solBackToLife);

	}
}
//----------------------------------------------------------------------------------------------------------------------------//
//for chess when the pawn become queen.
void board::upgradePawnToQueen(soldier* Pawn)
{
	soldier* newQueen = new queen();
	int* location = Pawn->getSquare().getLocation();
	if (location[0] == 0)
		player2.upgradeSoldier(Pawn, newQueen);
	else
		player1.upgradeSoldier(Pawn, newQueen);

	Board[location[0]][location[1]].setSoldier(nullptr);
	Board[location[0]][location[1]].setSoldier(newQueen);
	newQueen->setSquare(Board[location[0]][location[1]]);
	delete Pawn;
}
//----------------------------------------------------------------------------------------------------------------------------//
// for checkers when the soldier become king.
void board::upgradeSoldierToKing(soldier* sol)
{
	soldier* newKing = new checkersKing();
	int* location = sol->getSquare().getLocation();
	if (location[0] == 0)
		player2.upgradeSoldier(sol, newKing);
	else
		player1.upgradeSoldier(sol, newKing);

	Board[location[0]][location[1]].setSoldier(nullptr);
	Board[location[0]][location[1]].setSoldier(newKing);
	newKing->setSquare(Board[location[0]][location[1]]);
	delete sol;

}

void board::save(ostream& out)
{
	out.write(rcastc(&sizeOfBoard), sizeof(sizeOfBoard));
	if (!out.good())
		throw invalid_argument("The save failed.");
	for (int i = 0;i < sizeOfBoard;i++)
	{
		for (int j = 0;j < sizeOfBoard;j++)
			Board[i][j].save(out);
	}
}

//----------------------------------------------------------------------------------------------------------------------------//
void board::printBoard() const
{
	int i, j;
	cout << "    ";
	for (i = 1; i <= sizeOfBoard;i++)
		cout << i << " ";
	cout << endl << " ";
	cout << "  ";
	for (i = 0; i < sizeOfBoard;i++)
		cout << "--";
	cout << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for colors.
	for (int i = 0; i < sizeOfBoard; i++)
	{
		cout.width(2);
		cout << (i + 1) << " ";
		for (int j = 0;j < sizeOfBoard;j++)
		{
			cout << "|";
			soldier* sol = nullptr;
			if(sizeOfBoard == 10 && Board[i][j].getStatus() == isValid::NOT_VALID)
				cout << "*";
			else if (Board[i][j].getTaken() == taken::EMPTY || Board[i][j].getStatus() == isValid::NOT_VALID)
				cout << " ";
			else if (Board[i][j].getTaken() == taken::FULL1)
			{
				SetConsoleTextAttribute(hConsole, 15);
				sol = Board[i][j].getSoldierFromSquare();
				sol->printSoldier();
			}
			else if (Board[i][j].getTaken() == taken::FULL2)
			{
				SetConsoleTextAttribute(hConsole,12);
				sol = Board[i][j].getSoldierFromSquare();
				sol->printSoldier();
			}
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << "|" << endl;
	}
	cout << "   ";
	for (i = 0; i < sizeOfBoard;i++)
		cout << "--";
	cout << endl;

}
//--------------------------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const board& Board)
{
	Board.printBoard();
	return os;
}
bool board::checkIfBound(int ind1, int ind2) const
{
	if (ind1 >= 0 && ind1 <= sizeOfBoard - 1 && ind2 >= 0 && ind2 <= sizeOfBoard - 1)
		return true;
	return false;
}
//const listOfSquares& board::findRisks(int ind1, int ind2)
//{
//	taken currPlayer = Board[ind1][ind2].getTaken();
//	soldier* sol = Board[ind1][ind2].getSoldierFromSquare();
//	if (currPlayer == taken::FULL1)
//	{
//		player2.findRisksAndUpdateList(sol, Board[ind1][ind2]);
//	}
//	else
//		player1.findRisksAndUpdateList(sol, Board[ind1][ind2]);
//
//	return sol->getListOfRisks();
//
//}