#pragma once
#include "chess.h"
#include <algorithm>
class game;
class board;
class queenOfAmazonas;
class amazonas :  public game
{
public:
	amazonas(typeGame type, int sizeBoard);
	amazonas(typeGame& f_currgame, winner f_winner, statusGame f_statusGame, currTurn f_currTurn, istream& inFile):game(f_currgame, f_winner, f_statusGame, f_currTurn, inFile){}

	virtual ~amazonas() {};
public:
	virtual void checkRisks(int x, int y);
	virtual bool gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier);
	virtual bool checkIfTheNotOver();
	virtual void printName();
};

