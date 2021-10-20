#pragma once
#include "amazonas.h"
class chess;
class checkers: public game
{
public:
	checkers(typeGame type, int sizeBoard);
	checkers(typeGame& f_currgame, winner f_winner, statusGame f_statusGame, currTurn f_currTurn, istream& inFile) :game(f_currgame, f_winner, f_statusGame, f_currTurn, inFile) {}
	virtual ~checkers() {};

public:
	virtual void checkRisks(int x, int y);
	virtual bool checkIfTheNotOver();
	virtual void printName();
	virtual bool gamePlay(int fromX, int fromY, int toX, int toY, bool withSoldier);

	void possibleRisks(int x, int y, direction dir, taken opPlayer);
	bool emptyBehind(int x, int y);
	const direction& whatDirection(int fromX, int fromY, int toX, int toY);

};

