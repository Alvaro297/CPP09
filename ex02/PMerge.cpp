#include "PMerge.hpp"

PMerge::PMerge() : pMergueDeque() , pMergueVector (), timeToStart(clock()), timeToEnd(0) {}

PMerge::~PMerge() {}

void PMerge::addToVector(long value)
{
	pMergueVector.push_back(value);
}
void PMerge::addToDeque(long value)
{
	pMergueDeque.push_back(value);
}