#include "Transition.h"


#include "AbstractMatchSymbol.h"

#include <stdexcept>
using namespace std;


Transition::Transition(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState)
	:	mName{ name },
		mMatchSymbol{ matchSymbol },
		mNextState{ nextState }
{
	if (!matchSymbol || !nextState) {
		throw invalid_argument("Transition::Transition : Invalid constructor argument. Both matchSymbol and nextState arguments must be defined.");
	}
}

Transition::~Transition()
{
	delete mMatchSymbol;
}

bool Transition::isTransiting(symbol_t symbol) const
{
	return mMatchSymbol->isMatching(symbol);
}


