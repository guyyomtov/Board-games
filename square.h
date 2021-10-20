#pragma once
#include <iostream>
#include <stdexcept>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
class soldier;
using namespace std;
enum class isValid { VALID, NOT_VALID };
enum class taken { EMPTY, FULL1, FULL2 };

class square {

public:
	square();
	square(istream& inFile);
	square(int i, int j, soldier* s, taken currPlayer = taken::EMPTY);
	square(const square& other);
	square(square&& other);
	virtual ~square();

public:
	void initValid();
	void setLocation(int i, int j);
	const isValid& getStatus()const;
	const taken& getTaken() const;
	int* getLocation()const;
	void setTaken(taken curr);
	void setValid(isValid curr);
	const square& operator=(const square& other);
	const square& operator=(square&& other);
	soldier* getSoldierFromSquare()const;
	void setSoldier( soldier* sol);
	bool operator==(const square& other) const;
	void initStatusOfCheckers(int i, int j);
	void save(ostream& out);
	friend void checkFile(iostream& ios);

private:
	isValid m_status;
	taken m_curr;
	int* location;
	soldier* m_soldier;
};
