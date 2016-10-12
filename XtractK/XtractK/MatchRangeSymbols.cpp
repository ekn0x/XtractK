#include "MatchRangeSymbols.h"

using namespace std;


MatchRangeSymbols::MatchRangeSymbols(symbol_t const first, symbol_t const last)
	: mFirst{ first }, mLast{ last }
{
}

bool MatchRangeSymbols::isMatching(symbol_t symbol) const
{
	return (symbol >= mFirst && symbol <= mLast) ? true : false;
}

AbstractMatchSymbol* MatchRangeSymbols::clone() const
{
	return new MatchRangeSymbols(mFirst, mLast);
}