#include "TransitionCounter.h"




TransitionCounter::TransitionCounter(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState)
	:	AbstractBehavioralTransition(name, matchSymbol, nextState),
		mCount{ 0 }
{
}


void TransitionCounter::reset()
{
	mCount = 0;
}

//#define TEST_TEMPORAIRE_TO_REMOVE
#ifdef TEST_TEMPORAIRE_TO_REMOVE
#include <iostream>
using namespace std;
void TransitionCounter::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	cout << curSymbol << " : " << name() << " (" << mCount << ")" << endl;
	++mCount;
}
#else
void TransitionCounter::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	++mCount;
}
#endif


