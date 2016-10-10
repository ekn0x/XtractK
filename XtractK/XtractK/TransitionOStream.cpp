#include "TransitionOStream.h"



TransitionOStream::TransitionOStream(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream)
	:	TransitionCounter(name, matchSymbol, nextState),
		mStream{ stream }
{
}





