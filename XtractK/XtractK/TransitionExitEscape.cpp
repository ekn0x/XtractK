#include "TransitionExitEscape.h"



TransitionExitEscape::TransitionExitEscape(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}

void TransitionExitEscape::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);

	*mStream << prevSymbol << curSymbol;
}
