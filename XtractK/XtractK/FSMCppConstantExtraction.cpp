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

#include "MatchAllSymbols.h"
#include "MatchSingleSymbol.h"
#include "MatchNotSingleSymbol.h"
#include "MatchListSymbols.h"
#include "MatchNotListSymbols.h"
#include "Range.h"
#include "MatchRangeSymbols.h"
#include "MatchListRangeSymbols.h"
#include "MatchNotListRangeSymbols.h"
#include "MatchNotRangeSymbols.h"

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
	sInteger = new State("Integer", false);
	sMinus = new State("Minus", false);
	sDouble = new State("Double", false);
	sFloat = new State("Float", false);
	sZero = new State("Zero", false);
	sOctal = new State("Octal", false);
	sBinary = new State("Binary", false);
	sHexa = new State("HexaDecimal", false);

	// Create transitions
	tEnterSlash = new Transition("EnterSlash", new MatchSingleSymbol('/'), sSlash);
	tCancelSlash = new Transition("CancelSlash", new MatchNotListSymbols({ '*', '/' }), sCode);

	tEnterCommentCStyle = new TransitionCounter("EnterCommentCStyle", new MatchSingleSymbol('*'), sCommentCStyle);
	tCharCommentCStyle = new Transition("CharCommentCStyle", new MatchNotSingleSymbol('*'), sCommentCStyle);
	tEnterStar = new Transition("EnterStar", new MatchSingleSymbol('*'), sCommentCStyleStar);
	tCancelStar = new Transition("CancelStar", new MatchNotListSymbols({ '/', '*' }), sCommentCStyle);
	tCommentStar = new Transition("CommentStar", new MatchSingleSymbol('*'), sCommentCStyleStar);
	tExitCommentCStyle = new Transition("ExitCommentCStyle", new MatchSingleSymbol('/'), sCode);

	tEnterCommentCppStyle = new TransitionCounter("EnterCommentCppStyle", new MatchSingleSymbol('/'), sCommentCppStyle);
	tCharCommentCppStyle = new Transition("CharCommentCppStyle", new MatchNotListSymbols({ '\\', '\n' }), sCommentCppStyle);
	tExitCommentCppStyle = new Transition("ExitCommentCppStyle", new MatchSingleSymbol('\n'), sCode);
	tEnterEscapeCharComCppStyle = new Transition("EnterEscapeCharComCppStyle", new MatchSingleSymbol('\\'), sCommentCppStyleEscapeChar);
	tExitEscapeCharComCppStyle = new Transition("ExitEscapeCharComCppStyle", new MatchAllSymbols(), sCommentCppStyle);

	tEnterString = new TransitionNewComment("EnterString", new MatchSingleSymbol('"'), sString, mFileStatistics, linePaddingLength);
	tExitString = new TransitionExitingCStyle("ExitString", new MatchListSymbols({ '"', '\n' }), sCode);
	tEnterEscapeCharString = new Transition("EnterEscapeCharString", new MatchSingleSymbol('\\'), sStringEscapeChar);
	tExitEscapeCharString = new TransitionBackToComment("ExitEscapeCharString", new MatchAllSymbols(), sString);
	tHoldString = new TransitionInComment("HoldStringConstant", new MatchAllSymbols(), sString);

	tEnterCharacter = new TransitionNewComment("EnterCharacter", new MatchSingleSymbol('\''), sCharacter, mFileStatistics, linePaddingLength);
	tExitCharacter = new TransitionExitingCStyle("ExitCharacter", new MatchListSymbols({ '\'', '\n' }), sCode);
	tEnterEscapeCharCharacter = new Transition("EnterEscapeCharCharacter", new MatchSingleSymbol('\\'), sCharacterEscapeChar);
	tExitEscapeCharCharacter = new TransitionBackToComment("ExitEscapeCharCharacter", new MatchAllSymbols(), sCharacter);
	tHoldChar = new TransitionInComment("HoldCharConstant", new MatchAllSymbols(), sCharacter);
	
	//Integers
	tEnterInteger = new TransitionNewComment("EnterInteger", new MatchRangeSymbols('1', '9'), sInteger, mFileStatistics, linePaddingLength);
	tEnterIntegerFromMinus = new TransitionInComment("EnterIntegerFromMinus", new MatchRangeSymbols('0', '9'), sInteger);
	tHoldInteger = new TransitionInComment("HoldInteger", new MatchRangeSymbols('0', '9'), sInteger);

	//Doubles
	tEnterDouble = new TransitionNewComment("EnterDouble", new MatchSingleSymbol('.'), sDouble, mFileStatistics, linePaddingLength);
	tEnterDoubleFromStates = new TransitionInComment("EnterDoubleFromStates", new MatchSingleSymbol('.'), sDouble);
	tHoldDouble = new TransitionInComment("HoldDouble", new MatchRangeSymbols('0', '9'), sDouble);

	//Floats
	tEnterFloat = new TransitionInComment("EnterFloat", new MatchListSymbols({ 'f', 'F' }), sFloat);

	//Minus
	tEnterMinus = new TransitionNewComment("EnterMinus", new MatchSingleSymbol('-'), sMinus, mFileStatistics, linePaddingLength);

	//Zero
	tEnterZero = new TransitionNewComment("EnterZero", new MatchSingleSymbol('0'), sZero, mFileStatistics, linePaddingLength);

	//Binaries
	tEnterBinary = new TransitionInComment("EnterBinary", new MatchListSymbols({ 'b', 'B' }), sBinary);
	tHoldBinary = new TransitionInComment("HoldBinary", new MatchRangeSymbols('0', '1'), sBinary);

	//Octals
	tEnterOctal = new TransitionInComment("EnterOctal", new MatchRangeSymbols('0', '7'), sOctal);
	tHoldOctal = new TransitionInComment("HoldOctal", new MatchRangeSymbols('0', '7'), sOctal);

	//HexaDecimals
	tEnterHexa = new TransitionInComment("EnterHexa", new MatchListSymbols({ 'x', 'X' }), sHexa);
	tHoldHexa = new TransitionInComment("HoldHexa", new MatchListRangeSymbols({ Range('0', '9'), Range('A', 'F'), Range('a', 'f') }), sHexa);

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
	addState(sInteger);
	addState(sMinus);
	addState(sDouble);
	addState(sFloat);
	addState(sZero);
	addState(sOctal);
	addState(sBinary);
	addState(sHexa);

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
