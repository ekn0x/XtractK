#include "State.h"


#include <algorithm>

#include "Transition.h"

State::State(string const & name, bool accepting)
	:	mName{ name }, 
		mAccepting{ accepting }
{
}

State::~State()
{
	for_each(mTransitions.begin(), mTransitions.end(), deleteTransition);
}

void State::addTransition(Transition * transition)
{
	if (transition == nullptr) {
		// throw
	}

	mTransitions.push_back(transition);
}

Transition * State::isTransiting(symbol_t curSymbol)
{
	for (const auto & transition : mTransitions) {
		if (transition->isTransiting(curSymbol)) {
			return transition;
		}
	}

	return nullptr;
}

void State::deleteTransition(Transition * & transition)
{
	delete transition;
}