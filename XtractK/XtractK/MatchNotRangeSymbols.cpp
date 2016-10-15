#include "MatchNotRangeSymbols.h"
#include "Range.h"
using namespace std;


MatchNotRangeSymbols::MatchNotRangeSymbols(symbol_t const first, symbol_t const last)
	: MatchRangeSymbols{ first, last }
{
}

bool MatchNotRangeSymbols::isMatching(symbol_t symbol) const
{
	return !MatchRangeSymbols::isMatching(symbol);
}

AbstractMatchSymbol* MatchNotRangeSymbols::clone() const
{
	return new MatchNotRangeSymbols(MatchRangeSymbols::mRange->getFirst(), MatchRangeSymbols::mRange->getLast());
}
