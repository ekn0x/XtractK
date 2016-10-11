#include "FSMCppConstantExtraction.h"


#include "FSMFileStatistics.h"

#include "State.h"
#include "Transition.h"
#include "TransitionCounter.h"
#include "TransitionNewComment.h"
#include "TransitionInComment.h"
#include "TransitionBackToComment.h"
#include "TransitionExitingCStyle.h"

#include "Transition.h"
#include "TransitionCounter.h"
#include "TransitionNewComment.h"
#include "TransitionInComment.h"
#include "TransitionBackToComment.h"
#include "TransitionExitingCStyle.h"
#include "TransitionExitingCppStyle.h"

#include "TransitionExitEscape.h"
#include "TransitionKChar.H"
#include "TransitionExitK.h"

#include "MatchAllSymbols.h"
#include "MatchSingleSymbol.h"
#include "MatchNotSingleSymbol.h"
#include "MatchListSymbols.h"
#include "MatchNotListSymbols.h"

FSMCppConstantExtraction::FSMCppConstantExtraction(FSMFileStatistics const & mFileStatistics, int linePaddingLength)
	: FiniteStateMachine()
{
	// Create states
	sCode = new State("Code", true);
	sSlash = new State("Slash", false);
	sCommentCStyle = new State("CommentCStyle", false);
	sCommentCStyleStar = new State("CommentCStyleStar", false);
	sCommentCppStyle = new State("CommentCppStyle", false);
	sCommentCppStyleEscapeChar = new State("CommentCppStyleEscapeChar", false);
	sString = new State("String", false);
	sStringEscapeChar = new State("StringEscapeChar", false);
	sCharacter = new State("Character", false);
	sCharacterEscapeChar = new State("CharacterEscapeChar", false);

	// Create transitions
	tEnterSlash = new Transition("EnterSlash", new MatchSingleSymbol('/'), sSlash);
	tCancelSlash = new Transition("CancelSlash", new MatchNotListSymbols({ '*', '/' }), sCode);

	tEnterCommentCStyle = new TransitionNewComment("EnterCommentCStyle", new MatchSingleSymbol('*'), sCommentCStyle, mFileStatistics, linePaddingLength);
	tCharCommentCStyle = new TransitionInComment("CharCommentCStyle", new MatchNotSingleSymbol('*'), sCommentCStyle);
	tEnterStar = new Transition("EnterStar", new MatchSingleSymbol('*'), sCommentCStyleStar);
	tCancelStar = new TransitionBackToComment("CancelStar", new MatchNotListSymbols({ '/', '*' }), sCommentCStyle);
	tCommentStar = new TransitionInComment("CommentStar", new MatchSingleSymbol('*'), sCommentCStyleStar);
	tExitCommentCStyle = new TransitionExitingCStyle("ExitCommentCStyle", new MatchSingleSymbol('/'), sCode);

	tEnterCommentCppStyle = new TransitionNewComment("EnterCommentCppStyle", new MatchSingleSymbol('/'), sCommentCppStyle, mFileStatistics, linePaddingLength);
	tCharCommentCppStyle = new TransitionInComment("CharCommentCppStyle", new MatchNotListSymbols({ '\\', '\n' }), sCommentCppStyle);
	tExitCommentCppStyle = new TransitionExitingCppStyle("ExitCommentCppStyle", new MatchSingleSymbol('\n'), sCode);
	tEnterEscapeCharComCppStyle = new Transition("EnterEscapeCharComCppStyle", new MatchSingleSymbol('\\'), sCommentCppStyleEscapeChar);
	tExitEscapeCharComCppStyle = new TransitionBackToComment("ExitEscapeCharComCppStyle", new MatchAllSymbols(), sCommentCppStyle);

	tEnterString = new TransitionCounter("EnterString", new MatchSingleSymbol('"'), sString);
	tExitString = new TransitionExitK("ExitString", new MatchListSymbols({ '"', '\n' }), sCode);
	tEnterEscapeCharString = new Transition("EnterEscapeCharString", new MatchSingleSymbol('\\'), sStringEscapeChar);
	tExitEscapeCharString = new TransitionExitEscape("ExitEscapeCharString", new MatchAllSymbols(), sString);
	tHoldString = new TransitionKChar("HoldStringConstant", new MatchAllSymbols(), sString);

	tEnterCharacter = new TransitionCounter("EnterCharacter", new MatchSingleSymbol('\''), sCharacter);
	tExitCharacter = new TransitionExitK("ExitCharacter", new MatchListSymbols({ '\'', '\n' }), sCode);
	tEnterEscapeCharCharacter = new Transition("EnterEscapeCharCharacter", new MatchSingleSymbol('\\'), sCharacterEscapeChar);
	tExitEscapeCharCharacter = new TransitionExitEscape("ExitEscapeCharCharacter", new MatchAllSymbols(), sCharacter);
	tHoldChar = new TransitionKChar("HoldCharConstant", new MatchAllSymbols(), sCharacter);

	// Add transitions to states
	sCode->addTransition(tEnterSlash);
	sCode->addTransition(tEnterString);
	sCode->addTransition(tEnterCharacter);

	sSlash->addTransition(tCancelSlash);
	sSlash->addTransition(tEnterCommentCStyle);
	sSlash->addTransition(tEnterCommentCppStyle);

	sCommentCStyle->addTransition(tCharCommentCStyle);
	sCommentCStyle->addTransition(tEnterStar);

	sCommentCStyleStar->addTransition(tCancelStar);
	sCommentCStyleStar->addTransition(tCommentStar);
	sCommentCStyleStar->addTransition(tExitCommentCStyle);

	sCommentCppStyle->addTransition(tCharCommentCppStyle);
	sCommentCppStyle->addTransition(tExitCommentCppStyle);
	sCommentCppStyle->addTransition(tEnterEscapeCharComCppStyle);
	sCommentCppStyleEscapeChar->addTransition(tExitEscapeCharComCppStyle);

	sString->addTransition(tExitString);
	sString->addTransition(tEnterEscapeCharString);
	sString->addTransition(tHoldString);
	sStringEscapeChar->addTransition(tExitEscapeCharString);

	sCharacter->addTransition(tExitCharacter);
	sCharacter->addTransition(tEnterEscapeCharCharacter);
	sCharacter->addTransition(tHoldChar);
	sCharacterEscapeChar->addTransition(tExitEscapeCharCharacter);

	// Add states to FSM
	addState(sCode);
	addState(sSlash);
	addState(sCommentCStyle);
	addState(sCommentCStyleStar);
	addState(sCommentCppStyle);
	addState(sCommentCppStyleEscapeChar);
	addState(sString);
	addState(sStringEscapeChar);
	addState(sCharacter);
	addState(sCharacterEscapeChar);

	// Assign initial state
	setInitialState(sCode);
}

uint32_t FSMCppConstantExtraction::cStyleCommentCount() const
{
	return tEnterCommentCStyle->count();
}

uint32_t FSMCppConstantExtraction::cppStyleCommentCount() const
{
	return tEnterCommentCppStyle->count();
}

uint32_t FSMCppConstantExtraction::stringCount() const
{
	return tEnterString->count();
}

uint32_t FSMCppConstantExtraction::characterCount() const
{
	return tEnterCharacter->count();
}
