#include "TransitionInComment.h"



TransitionInComment::TransitionInComment(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}



void TransitionInComment::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);

	*mStream << curSymbol;
}





