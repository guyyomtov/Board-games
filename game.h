#pragma once
#include "board.h"
#include <list>
class square;
enum class winner { PLAYER1WIN, PLAYER2WIN, NO_ONE };
enum class statusGame { OVER, NOT_OVER };
enum class currTurn { PLAYER1T, PLAYER2T };
enum class typeGame{ CHECKERS = 1, GAME_OF_AMAZONAS, CHESS};
class game
{

public:
	game(typeGame currgame, int sizeBoard);
	game(typeGame& f_currgame, winner f_winner, statusGame f_statusGame, currTurn f_currTurn, istream& inFile);
	game(const game& other);
	game(game&& other);
	virtual ~game() {};

public:
	void checkValidMoveOfSoldier(int x, int y);
	virtual void checkRisks(int x, int y) = 0;
	virtual bool gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier) = 0;
	virtual bool checkIfTheNotOver()=0;
	virtual void printName() = 0;

	void updateTurn();
	bool checkIfMyTurn(int fromX, int fromY);
	void printValidMove() const;
	void printRisks() const;
	void freeListOfValidMove();
	void freeListOfRisks();
	void printBoardAndDetailsOnTheGame();
	const statusGame& getStatusOfGame() const;
	const taken& getTaken(int x, int y) const;
	const isValid& getIsValid(int x, int y) const;
	int getSizeOfBoard()const;
	void save(ostream& out);
	void load(istream& in);
	friend void checkFile(iostream& ios);

public:
	const game& operator=(const game& other);
	const game& operator=(game&& other);

public:
	void printList(const list<square>& lst)const;

protected:
	typeGame g_currGame;
	board g_board;
	winner g_winner;
	statusGame g_statusGame;
	currTurn g_currTurn;
	list<square> g_listOfValidMove;
	list<square> g_risks;
};
 

