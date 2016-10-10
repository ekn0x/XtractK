#include "TransitionBackToComment.h"



TransitionBackToComment::TransitionBackToComment(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	: TransitionOStream(name, matchSymbol, nextState, stream)
{
}



void TransitionBackToComment::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);

	*mStream << prevSymbol << curSymbol;
}





