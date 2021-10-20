#pragma once
//#include "listOfSquares.h"
#include <list>
#include "square.h"
/*This class is the general soldier and every type on the other soldiers inherit from this class.*/
enum class direction { LEFT, UPLEFT, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFTUP, RIGHTUP, RIGHTDOWN, LEFTDOWN };

class board;
class soldier { 
public:
	soldier();
	soldier(const square& sq);
	soldier(const soldier& other);
	soldier(soldier&& other);
	virtual ~soldier() {};
public:
	const square& getSquare()const;
	void setSquare(const square& sq);
	virtual void checkValidMove(int x, int y, board& g_board, bool checkRiskOnKing) = 0;
	void checkPossibleMove(int x, int y, direction currDir, board& g_board, bool checkRiskOnKing);
	bool checkIfValidMove(int x, int y, int moveX, int moveY, taken currPlayer, board& g_board, bool checkRiskOnKing);
	const soldier& operator=(const soldier& other);
	const soldier& operator=(soldier&& other);
	void printValidMoves()const;
	list<square>& getListOfValidMove();
	list<square>& getListOfRisks();
	/*bool isExists(const square& sq, const list<square>& lst);*/
	void updateList(const square& sq);
	bool checkRisksOnKing(int x, int y, int moveX, int moveY, board& g_board);
	void freeListOfValidMoves();
	void freeListOfRisks();
	virtual void printSoldier() = 0;

protected:
	list <square> s_listOfValidMoves;
	list <square> s_listOfRisks;
	square s_square; 
};


