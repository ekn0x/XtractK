#include "AbstractBehavioralState.h"


#include "AbstractBehavioralTransition.h"


AbstractBehavioralState::AbstractBehavioralState(const string & name, bool accepting)
	: State(name, accepting)
{
}

void AbstractBehavioralState::reset()
{
	for (auto const & transition : mTransitions) {
		AbstractBehavioralTransition * behavioralTransition = dynamic_cast<AbstractBehavioralTransition*>(transition);
		if (behavioralTransition) {
			behavioralTransition->reset();
		}
	}
}
