#include "MatchListRangeSymbols.h"
#include "Range.h"

#include <algorithm>

using namespace std;

MatchListRangeSymbols::MatchListRangeSymbols(list<Range> const & listRange)
	: mListRange{ listRange }
{
}

MatchListRangeSymbols::MatchListRangeSymbols(initializer_list<Range> const & listRange)
	: mListRange{ listRange }
{
}

bool MatchListRangeSymbols::isMatching(symbol_t symbol) const
{
	bool find = false;
	for (auto it = mListRange.begin(); it!=mListRange.end() || !find ; ++it)
	{
		find = it->isInRange(symbol);
	}
	

	return find;
}

AbstractMatchSymbol* MatchListRangeSymbols::clone() const
{
	return new MatchListRangeSymbols(mListRange);
}
