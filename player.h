#pragma once
#include "checkersKing.h"
#include <vector>
//class square;
class soldier;
const int MaxSoldier = 16;
class player {

public:
	player(taken curr ,int size = 0);
	//player(taken toWho);
	player(const player& other);
	player(player&& other);
	~player();
public:
	const player& operator=(const player& other);
	const player& operator=(player&& other);
	void freeArrayOfPointer();
	void setSoldierInArr(soldier* s);
	const soldier& getSoldier(int index) const;
	//void updateRegularMovmentOfSoldier(int fromX, int fromY, int toX, int toY);
	void deleteSoldierFromArr(int x, int y);
	vector<soldier*> getArrayOfSoldiers()const;
	const int getSizeOfArr()const;
	void checkRisksInArr(soldier* sol, const square& sq, board& g_board);
	void updateArr(soldier* eatenSol);
	void setKing(soldier* sol) { theKing = sol; };
	soldier* getKing() const { return theKing; };
	soldier* addSizeToArray();
	bool checkValidmovesInArrOfSoldiers(board& g_board);
	void upgradeSoldier(soldier* Pawn, soldier* queen);
	void mallocArr(int size);

private:
	soldier* theKing;
	/*arrOfPointer<soldier*> SoldiersPlayer;*/
	vector<soldier*> SoldiersPlayer;
	taken curr;
	int countEatenSol = 0;
};


