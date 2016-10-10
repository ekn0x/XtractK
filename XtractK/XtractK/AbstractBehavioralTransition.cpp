#include "AbstractBehavioralTransition.h"



AbstractBehavioralTransition::AbstractBehavioralTransition(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState)
	: Transition(name, matchSymbol, nextState)
{
}



