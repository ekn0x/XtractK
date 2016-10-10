#include "TransitionExitingCppStyle.h"



TransitionExitingCppStyle::TransitionExitingCppStyle(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}



void TransitionExitingCppStyle::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);

	// pas besoin
	// *mStream << curSymbol << endl;
}





