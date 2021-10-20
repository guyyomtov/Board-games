#pragma once
#include "player.h"
#include <windows.h>
#include <fstream>
class soldier;
class player;
class square;
class knight;
class game;
class queenOfAmazonas;
class checkersSoldier;
//enum class direction { LEFT, UPLEFT, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFTUP, RIGHTUP, RIGHTDOWN, LEFTDOWN};
//we dont create operator= because we dont use it!(there is only one board each game). 
const int SIZE_CHESS = 8;
const int SIZE_CHECKERS = 8;
const int SIZE_AMAZONAS = 10;
const int MAX_SOLDIERS_CHESS = 16;
const int MAX_SOLDIERS_CHECKERS = 8;
const int MAX_SOLDIERS_AMAZONAS = 4;
class board {
public:
	/*board(currGame curr_game);*/
	//board();
	board(int typeGame, int size);
	board(istream& inFile);
	board(const board& other);
	board(board&& other);
	~board();
public:
	void initChess();
	void initAmazonas();
	void initCheckers();
	void freeBoard();
	const isValid& getStatusOfSquare(int x, int y) const;
	const taken& getTakenOfSquare(int x, int y) const;
	const square& getSquare(int x, int y)const;
	void printBoard() const;
	bool updateBoard(int fromX, int fromY, int toX, int toY);
	void updateBoard(int fromX, int fromY, int toX, int toY, bool queenMove);
	void updateBoard(int fromX, int fromY, int toX, int toY, direction curDir);
	void checkIfEatOrRegularMove(int crossX, int crossY, taken currPlayer);
	bool checkValidMovesInArr(taken currPlayer, board& g_board);
	bool checkIfBound(int ind1, int ind2) const;
	soldier* getSoldier(int x, int y) const;
	void findRisks(int ind1, int ind2);
	soldier* getKingFromPlayer(taken currPlayer);
	void undoUpdateBoard(int fromX, int fromY, int toX, int toY, bool eaten);
	void upgradePawnToQueen(soldier* Pawn);
	void upgradeSoldierToKing(soldier* sol);
	int getSizeOfBoard()const { return sizeOfBoard; };
	void save(ostream& out);
	soldier* checkWhichSoldierToAllocate(char* type);

public:
	const board& operator=(board&& other);
	const board& operator=(const board& other);
	friend ostream& operator<<(ostream& os, const board& Board);

private:
	vector<vector<square>> Board;
	int sizeOfBoard;
	player player1;
	player player2;
};

