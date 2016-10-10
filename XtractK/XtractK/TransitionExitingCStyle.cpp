#include "TransitionExitingCStyle.h"



TransitionExitingCStyle::TransitionExitingCStyle(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}



void TransitionExitingCStyle::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);
	
	// pas besoin
	// *mStream << prevSymbol << curSymbol << endl << endl;
}





