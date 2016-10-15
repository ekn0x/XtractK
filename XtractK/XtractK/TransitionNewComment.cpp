#include "TransitionNewComment.h"

#include <iomanip>

TransitionNewComment::TransitionNewComment(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, FSMFileStatistics const & fileStatistics, int linePaddingLength, ostream * stream)
	:	TransitionOStream(name, matchSymbol, nextState, stream),
		mFileStatistics{ fileStatistics },
		mLinePaddingLength{ linePaddingLength }
{
}



void TransitionNewComment::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	TransitionCounter::process(prevSymbol, curSymbol);
	
	*mStream << "Ligne " << setfill('0') << setw(mLinePaddingLength) << mFileStatistics.lineCount() << " - - - - -" << endl << prevSymbol << curSymbol;
}





