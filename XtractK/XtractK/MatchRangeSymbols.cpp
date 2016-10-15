#include "MatchRangeSymbols.h"
#include "Range.h"
using namespace std;


MatchRangeSymbols::MatchRangeSymbols(symbol_t const first, symbol_t const last)
{
	mRange = new Range(first, last);
}

MatchRangeSymbols::~MatchRangeSymbols()
{
	delete mRange; // liberation de la memoire
}

bool MatchRangeSymbols::isMatching(symbol_t symbol) const
{
	return mRange->isInRange(symbol);
}

AbstractMatchSymbol* MatchRangeSymbols::clone() const
{
	return new MatchRangeSymbols(mRange->getFirst(), mRange->getLast());
}
