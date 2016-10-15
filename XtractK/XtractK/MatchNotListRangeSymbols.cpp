



#include "MatchListRangeSymbols.h"
#include "MatchNotListRangeSymbols.h"
#include "Range.h"

MatchNotListRangeSymbols::MatchNotListRangeSymbols(list<Range> const & listRange)
	: MatchListRangeSymbols{ listRange }
{
}

MatchNotListRangeSymbols::MatchNotListRangeSymbols(initializer_list<Range> const & listRange)
	: MatchListRangeSymbols{ listRange }
{
}

bool MatchNotListRangeSymbols::isMatching(symbol_t symbol) const
{
	return !MatchListRangeSymbols::isMatching(symbol);
}

AbstractMatchSymbol* MatchNotListRangeSymbols::clone() const
{
	return new MatchNotListRangeSymbols(mListRange);
}
