#include "StateCounter.h"



StateCounter::StateCounter(const string & name, bool accepting)
	: AbstractBehavioralState(name, accepting)
{
}

void StateCounter::reset()
{
	mEnterCount = 0;
	mDoCount = 0;
	mExitCount = 0;
}
void StateCounter::entering(symbol_t prevSymbol, symbol_t curSymbol)
{
	++mEnterCount;
}
void StateCounter::doing(symbol_t prevSymbol, symbol_t curSymbol)
{
	++mDoCount;
}
void StateCounter::exiting(symbol_t prevSymbol, symbol_t curSymbol)
{
	++mExitCount;
}
