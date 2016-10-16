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
#include "TransitionExitConstant.h"

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
	sWord = new State("FreeWord", false);
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

	// free Words
	tEnterWord = new TransitionCounter("EnterWord", new MatchListRangeSymbols({ Range('a', 'z'), Range('A', 'Z') }), sWord);
	tHoldWord = new Transition("ExitWord", new MatchListRangeSymbols({ Range('a', 'z'), Range('A', 'Z'), Range('0', '9') }), sCode);
	tExitWord = new Transition("ExitWord", new MatchNotListRangeSymbols({ Range('a', 'z'), Range('A', 'Z'), Range('0', '9') }), sCode);
	
	//Integers
	tEnterIntegerFromCode = new TransitionNewComment("EnterInteger", new MatchRangeSymbols('1', '9'), sInteger, mFileStatistics, linePaddingLength);
	tEnterIntegerFromMinus = new TransitionNewComment("EnterIntegerFromMinus", new MatchRangeSymbols('0', '9'), sInteger, mFileStatistics, linePaddingLength);
	tEnterIntegerFromZero = new TransitionNewComment("EnterIntegerFromZero", new MatchNotListRangeSymbols({ Range('b','b'), Range('B', 'B'), Range('x','x'), Range('X','X'), Range('0','7'), Range('.', '.') }), sInteger, mFileStatistics, linePaddingLength);
	tHoldInteger = new TransitionInComment("HoldInteger", new MatchRangeSymbols('0', '9'), sInteger);
	tExitInteger = new TransitionExitConstant("ExitInteger", new MatchNotListRangeSymbols({ Range('.', '.'), Range('0', '9') }), sCode);

	//Doubles
	tEnterDoubleFromCode = new TransitionNewComment("EnterDouble", new MatchSingleSymbol('.'), sDouble, mFileStatistics, linePaddingLength);
	tEnterDoubleFromZero = new TransitionNewComment("EnterDoubleFromZero", new MatchSingleSymbol('.'), sDouble, mFileStatistics, linePaddingLength);
	tEnterDoubleFromMinus = new TransitionNewComment("EnterDoubleFromMinus", new MatchSingleSymbol('.'), sDouble, mFileStatistics, linePaddingLength);
	tEnterDoubleFromInteger = new TransitionInComment("EnterDoubleFromInteger", new MatchSingleSymbol('.'), sDouble);
	tHoldDouble = new TransitionInComment("HoldDouble", new MatchRangeSymbols('0', '9'), sDouble);
	tExitDouble = new TransitionExitConstant("ExitDouble", new MatchNotListRangeSymbols({ Range('.','.'), Range('f','f'), Range('F', 'F'), Range('0', '9') }), sCode);

	//Floats
	tEnterFloat = new TransitionInComment("EnterFloat", new MatchListSymbols({ 'f', 'F' }), sFloat);
	tExitFloat = new TransitionExitConstant("ExitFloat", new MatchAllSymbols(), sCode);

	//Minus
	tEnterMinus = new TransitionNewComment("EnterMinus", new MatchSingleSymbol('-'), sMinus, mFileStatistics, linePaddingLength);
	tExitMinus = new Transition("ExitMinusToCode", new MatchNotListRangeSymbols({ Range('.', '.'), Range('0', '9') }), sCode);

	//Zero
	tEnterZero = new Transition("EnterZero", new MatchSingleSymbol('0'), sZero);

	//Binaries
	tEnterBinary = new TransitionNewComment("EnterBinary", new MatchListSymbols({ 'b', 'B' }), sBinary, mFileStatistics, linePaddingLength);
	tHoldBinary = new TransitionInComment("HoldBinary", new MatchRangeSymbols('0', '1'), sBinary);
	tExitBinary = new TransitionExitConstant("ExitBinary", new MatchNotRangeSymbols('0', '1'), sCode);

	//Octals
	tEnterOctal = new TransitionNewComment("EnterOctal", new MatchRangeSymbols('0', '7'), sOctal, mFileStatistics, linePaddingLength);
	tHoldOctal = new TransitionInComment("HoldOctal", new MatchRangeSymbols('0', '7'), sOctal);
	tExitOctal = new TransitionExitConstant("ExitOctal", new MatchNotRangeSymbols('0', '7'), sCode);

	//HexaDecimals
	tEnterHexa = new TransitionNewComment("EnterHexa", new MatchListSymbols({ 'x', 'X' }), sHexa, mFileStatistics, linePaddingLength);
	tHoldHexa = new TransitionInComment("HoldHexa", new MatchListRangeSymbols({ Range('0', '9'), Range('A', 'F'), Range('a', 'f') }), sHexa);
	tExitHexa = new TransitionExitConstant("ExitHexa", new MatchNotListRangeSymbols({ Range('0','9'), Range('A','F'), Range('a', 'f') }), sCode);

	// Add transitions to states
	sCode->addTransition(tEnterSlash);
	sCode->addTransition(tEnterString);
	sCode->addTransition(tEnterCharacter);
	sCode->addTransition(tEnterWord);
	//sCode->addTransition(tEnterIntegerFromCode);
	//sCode->addTransition(tEnterMinus);
	//sCode->addTransition(tEnterDoubleFromCode);
	//sCode->addTransition(tEnterZero);

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

	sWord->addTransition(tHoldWord);
	sWord->addTransition(tExitWord);

	sInteger->addTransition(tEnterDoubleFromInteger);
	sInteger->addTransition(tHoldInteger);
	sInteger->addTransition(tExitInteger);

	sMinus->addTransition(tEnterDoubleFromMinus);
	sMinus->addTransition(tEnterIntegerFromMinus);
	sMinus->addTransition(tExitMinus);

	sDouble->addTransition(tEnterFloat);
	sDouble->addTransition(tHoldDouble);
	sDouble->addTransition(tExitDouble);

	sFloat->addTransition(tExitFloat);

	sZero->addTransition(tEnterBinary);
	sZero->addTransition(tEnterOctal);
	sZero->addTransition(tEnterHexa);
	sZero->addTransition(tEnterDoubleFromZero);
	sZero->addTransition(tEnterIntegerFromZero);

	sBinary->addTransition(tHoldBinary);
	sBinary->addTransition(tExitBinary);

	sOctal->addTransition(tHoldOctal);
	sOctal->addTransition(tExitOctal);

	sHexa->addTransition(tHoldHexa);
	sHexa->addTransition(tExitHexa);

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
