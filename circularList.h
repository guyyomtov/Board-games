#pragma once
#include <list>
#include "game.h"
class circularList
{
public:
	void insertDataToEndList(game* Game);
	game* goToTheNextValue();
	game* deleteValue();
	
private:
	list<game*> lst;
	list<game*> :: iterator iterCurrValue;
};

