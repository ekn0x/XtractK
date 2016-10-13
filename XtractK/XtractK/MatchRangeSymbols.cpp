#include "MatchRangeSymbols.h"

using namespace std;


MatchRangeSymbols::MatchRangeSymbols(symbol_t const first, symbol_t const last)
{
	mRange = new Range(first, last);
}

MatchRangeSymbols::~MatchrangeSymbols()
{
	delete mRange; // liberation de la memoire
}

bool MatchRangeSymbols::isMatching(symbol_t symbol) const
{
	return mRange->isInRange(symbol);
}

AbstractMatchSymbol* MatchRangeSymbols::clone() const
{
	return new MatchRangeSymbols(mFirst, mLast);
}
