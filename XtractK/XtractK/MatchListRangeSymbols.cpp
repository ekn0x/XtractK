#include "MatchListRangeSymbols.h"

#include <algorithm>

using namespace std;

MatchListRangeSymbols::MatchListRangeSymbols(initializer_list<Range> const & listRange)
	: mListRange{ listRange }
{
}

bool MatchListRangeSymbols::isMatching(symbol_t const & symbol)
{
	bool find = false;
	for (auto it = mListRange.begin(); it!=mListRange.end() || !find ;++it)
	{
		find = (*it).isInRange(symbol);
	}

	return find;
}
