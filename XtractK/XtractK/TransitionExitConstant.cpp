#include "TransitionExitConstant.h"



TransitionExitConstant::TransitionExitConstant(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}



void TransitionExitConstant::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);

	*mStream << endl << endl;
}

