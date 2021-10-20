#pragma once
#include "game.h"
class board;

class chess : public game {
public:
	chess(typeGame type, int sizeBoard);
	chess(typeGame& f_currgame, winner f_winner, statusGame f_statusGame, currTurn f_currTurn, istream& inFile) :game(f_currgame, f_winner, f_statusGame, f_currTurn, inFile) {}
	virtual ~chess() {};

public:
	virtual void checkRisks(int x, int y);
	virtual bool gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier) ;
	virtual bool checkIfTheNotOver() ;
	virtual bool checkIfBound(int ind1, int ind2) const;
	virtual void printName();
};

