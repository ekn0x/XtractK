#include "FiniteStateMachine.h"


#include "State.h"

#include <algorithm>
#include <stdexcept>
#include "AbstractBehavioralState.h"
#include "AbstractBehavioralTransition.h"
#include "TransitionOStream.h"
 
string FiniteStateMachine::mNoStateName{ "-no current state-" };


FiniteStateMachine::FiniteStateMachine()
	:	mPreviousSymbol{ '\0' },
		mRunning{ false },
		mInitialState{ nullptr },
		mCurrentState{ nullptr }
{
}

FiniteStateMachine::~FiniteStateMachine()
{
	for_each(mStates.begin(), mStates.end(), deleteState);
}


void FiniteStateMachine::addState(State * state)
{
	if (!state) {
		throw invalid_argument("FiniteStateMachine::addState :\nstate arguments must be defined.");
	}

	if (find(mStates.begin(), mStates.end(), state) != mStates.end()) {
		return;
	}

	mStates.push_back(state);
}
void FiniteStateMachine::setInitialState(State * initState)
{
	if (!initState) {
		throw invalid_argument("FiniteStateMachine::setInitialState :\ninitState arguments must be defined.");
	}

	if (find(mStates.begin(), mStates.end(), initState) == mStates.end()) {
		mInitialState = nullptr;
		throw invalid_argument("FiniteStateMachine::setInitialState :\ninitState arguments must exist in the previously inserted states.");
	}

	mInitialState = initState;
}

void FiniteStateMachine::setStream(ostream * stream)
{
	for (auto const & state : mStates) {
		for (auto const & transition : state->mTransitions) {
			TransitionOStream * oStreamTransition = dynamic_cast<TransitionOStream*>(transition);
			if (oStreamTransition) {
				oStreamTransition->setStream(stream);
			}
		}
	}
}

void FiniteStateMachine::resetBehavioralStates()
{
	for (auto const & state : mStates) {
		AbstractBehavioralState * abstractBehavioralState = dynamic_cast<AbstractBehavioralState*>(state);
		if (abstractBehavioralState) {
			abstractBehavioralState->reset();
		}
	}
}

void FiniteStateMachine::resetBehavioralTransitions()
{
	for (auto const & state : mStates) {
		for (auto const & transition : state->mTransitions) {
			AbstractBehavioralTransition * abstractBehavioralTransition = dynamic_cast<AbstractBehavioralTransition*>(transition);
			if (abstractBehavioralTransition) {
				abstractBehavioralTransition->reset();
			}
		}
	}
}

void FiniteStateMachine::start()
{
	if (mStates.size() == 0 || !mInitialState) {
		throw logic_error("FiniteStateMachine::start :\nFSM must contain at least one state and have already defined the initial state.");
	}

	if (mRunning) {
		stop();
	}

	resetBehavioralStates();
	resetBehavioralTransitions();

	mCurrentState = mInitialState;
	mRunning = true;
}
bool FiniteStateMachine::stop()
{
	if (!mRunning) {
		return false;
	}

	bool terminatedOnAcceptingState = mCurrentState->isAccepting();
	mCurrentState = mInitialState;
	mRunning = false;

	return terminatedOnAcceptingState;
}

void FiniteStateMachine::processBehavioralTransition(Transition * transition, symbol_t curSymbol)
{
	AbstractBehavioralTransition * behavioralTransition = dynamic_cast<AbstractBehavioralTransition*>(transition);
	if (behavioralTransition) {
		behavioralTransition->process(mPreviousSymbol, curSymbol);
	}
}

void FiniteStateMachine::exitCurrentBehavioralState(symbol_t curSymbol)
{
	AbstractBehavioralState * behavioralState = dynamic_cast<AbstractBehavioralState*>(mCurrentState);
	if (behavioralState) {
		behavioralState->exiting(mPreviousSymbol, curSymbol);
	}
}

void FiniteStateMachine::enterProcessCurrentBehavioralState(symbol_t curSymbol)
{
	AbstractBehavioralState * behavioralState = dynamic_cast<AbstractBehavioralState*>(mCurrentState);
	if (behavioralState) {
		behavioralState->entering(mPreviousSymbol, curSymbol);
		behavioralState->doing(mPreviousSymbol, curSymbol);
	}
}

void FiniteStateMachine::processCurrentBehavioralState(symbol_t curSymbol)
{
	AbstractBehavioralState * behaviorState = dynamic_cast<AbstractBehavioralState*>(mCurrentState);
	if (behaviorState) {
		behaviorState->doing(mPreviousSymbol, curSymbol);
	}
}

void FiniteStateMachine::processSymbol(symbol_t curSymbol)
{
	if (mRunning) {
		Transition * transition = mCurrentState->isTransiting(curSymbol);
		if (transition) {
			if (mCurrentState == transition->nextState()) {
				processBehavioralTransition(transition, curSymbol);
			} else {
				exitCurrentBehavioralState(curSymbol);

				processBehavioralTransition(transition, curSymbol);

				mCurrentState = transition->nextState();
				if (!mCurrentState) {
					throw logic_error("FiniteStateMachine::processSymbol :\nFSM current state is undefined!");
				}

				enterProcessCurrentBehavioralState(curSymbol);
			}
		} else {
			processCurrentBehavioralState(curSymbol);
		}

		mPreviousSymbol = curSymbol;
	}
}

string FiniteStateMachine::currentStateName() const
{
	if (!mCurrentState) {
		return mNoStateName;
	}

	return mCurrentState->name();
}


void FiniteStateMachine::deleteState(State * & state)
{
	delete state;
}
