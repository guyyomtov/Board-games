#include "circularList.h"

void circularList::insertDataToEndList(game* Game)
{
	lst.push_back(Game);
	iterCurrValue = --lst.end();
}

game* circularList::goToTheNextValue()
{
	++iterCurrValue;
	if (iterCurrValue == lst.end())
	{
		iterCurrValue = lst.begin();
	}
	return *iterCurrValue;
}

game* circularList::deleteValue()
{
	iterCurrValue = lst.erase(iterCurrValue);
	if (iterCurrValue == lst.end())
	{
		iterCurrValue = lst.begin();
	}
	if (lst.empty())
		return nullptr;
	return *iterCurrValue;
}
