#include "FSMFileStatistics.h"

#include "State.h"
#include "TransitionCounter.h"
#include "MatchAllSymbols.h"
#include "MatchSingleSymbol.h"
#include "MatchListSymbols.h"
#include "MatchNotListSymbols.h"

FSMFileStatistics::FSMFileStatistics()
	: FiniteStateMachine()
{
	// Create states
	mEmptyFile = new State("EmptyFile", true);
	mInLine = new State("InLine", true);

	// Create transitions
	mStartByLine = new TransitionCounter("StartByLine", new MatchSingleSymbol('\n'), mInLine);
	mStartBySpace = new TransitionCounter("StartBySpace", new MatchListSymbols({ ' ', '\t' }), mInLine);
	mStartByCharacter = new TransitionCounter("StartByCharacter", new MatchNotListSymbols({ '\n', ' ', '\t' }), mInLine);
	mLineCounter = new TransitionCounter("LineCounter", new MatchSingleSymbol('\n'), mInLine);
	mSpaceCounter = new TransitionCounter("SpaceCounter", new MatchListSymbols({ ' ', '\t'}), mInLine);
	mCharacterCounter = new TransitionCounter("CharacterCounter", new MatchNotListSymbols({ '\n', ' ', '\t' }), mInLine);

	// Add transitions to states
	mEmptyFile->addTransition(mStartByLine);
	mEmptyFile->addTransition(mStartBySpace);
	mEmptyFile->addTransition(mStartByCharacter);

	mInLine->addTransition(mLineCounter);
	mInLine->addTransition(mSpaceCounter);
	mInLine->addTransition(mCharacterCounter);

	// Add states to FSM
	addState(mEmptyFile);
	addState(mInLine);

	// Assign initial state
	setInitialState(mEmptyFile);
}

bool FSMFileStatistics::isFileEmpty() const
{
	return	mStartByLine->count() == 0 && 
			mStartBySpace->count() == 0 && 
			mStartByCharacter->count() == 0;
}

uint32_t FSMFileStatistics::lineCount() const
{
	if (isFileEmpty()) {
		return 0;
	} 

	return mStartByLine->count() + mLineCounter->count() + 1;
}

uint32_t FSMFileStatistics::spaceCount() const
{
	if (isFileEmpty()) {
		return 0;
	}

	return mStartBySpace->count() + mSpaceCounter->count();
}

uint32_t FSMFileStatistics::characterCount() const
{
	if (isFileEmpty()) {
		return 0;
	}

	return mStartByCharacter->count() + mCharacterCounter->count();
}
