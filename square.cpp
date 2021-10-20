#include "square.h"
#include "soldier.h"
square::square() :location(nullptr), m_soldier(nullptr)
{
}
square::square(istream& inFile): m_soldier(nullptr)
{
	inFile.read(rcastc(&m_status), sizeof(m_status));
	inFile.read(rcastc(&m_curr), sizeof(m_curr));
	location = new int[2];
	if (location == nullptr)
		throw bad_alloc();
	inFile.read(rcastc(&location[0]), sizeof(location[0]));
	inFile.read(rcastc(&location[1]), sizeof(location[1]));
	if (!inFile.good())
		throw invalid_argument("The load failed.");
}
square::square(int i, int j, soldier* s, taken currPlayer) : m_curr(currPlayer), m_soldier(s)
{
	setLocation(i, j);
	initValid();
}
square::square(const square& other) : m_curr(other.m_curr), m_status(other.m_status)
{
	setSoldier(other.m_soldier);
	location = new int[2];
	if (location == nullptr)
		throw bad_alloc();
	location[0] = other.location[0];
	location[1] = other.location[1];
}
square::square(square&& other) : m_curr(other.m_curr), m_status(other.m_status), m_soldier(other.m_soldier)
{
	location = other.location;
	other.location = nullptr;
}
void square::setLocation(int i, int j) //the location on the board
{
	location = new int[2];
	if (location == nullptr)
		throw bad_alloc();
	location[0] = i;
	location[1] = j;
}
void square::setTaken(taken curr)
{
	m_curr = curr;
}

void square::initValid()
{
	m_status = isValid::VALID;
}
void square::setValid(isValid curr)
{
	m_status = curr;
}
const isValid& square::getStatus()const
{
	return m_status;
}
const taken& square::getTaken() const
{
	return m_curr;
}
int* square::getLocation()const // return pointer
{
	return location;
}
square::~square()
{
	delete[] location;
}

const square& square::operator=(const square& other)
{
	if (this != &other)
	{
		delete[]location;
		location = new int[2];
		if (location == nullptr)
			throw bad_alloc();
		location[0] = other.location[0];
		location[1] = other.location[1];
		m_status = other.m_status;
		m_curr = other.m_curr;
		m_soldier = other.m_soldier;
	}
	return *this;
}
const square& square::operator=(square&& other)
{
	delete[] location;
	location = other.location;
	other.location = nullptr;
	m_status = other.m_status;
	m_curr = other.m_curr;
	m_soldier = other.m_soldier;
	other.m_soldier = nullptr;
	return *this;
}

soldier* square::getSoldierFromSquare() const
{
	return m_soldier;
}

void square::setSoldier(soldier* sol)
{
	m_soldier = sol;
}

bool square::operator==(const square& other) const
{
	if (this->location[0] == other.location[0] && this->location[1] == other.location[1] && this->m_curr == other.m_curr && this->m_status == other.m_status && this->m_soldier == this->m_soldier)
		return true;
	return false;
}

void square::initStatusOfCheckers(int i, int j)
{

	if (i % 2 == 0 && j % 2 == 1)
		m_status = isValid::VALID;
	else if (i % 2 == 1 && j % 2 == 0)
		m_status = isValid::VALID;
	else
	{
		m_status = isValid::NOT_VALID;
		m_curr = taken::EMPTY;
	}

}

void square::save(ostream& out)
{
	out.write(rcastc(&m_status), sizeof(m_status));
	out.write(rcastc(&m_curr), sizeof(m_curr));
	out.write(rcastc(&location[0]), sizeof(location[0]));
	out.write(rcastc(&location[1]), sizeof(location[1]));
	if (m_soldier != nullptr)
	{
		string type = typeid(*(m_soldier)).name();
		int len = type.length();
		out.write(rcastc(&len), sizeof(len));
		out.write(rcastcc(type.c_str()), len);
	}
	if (!out.good())
		throw invalid_argument("The save failed.");
}
