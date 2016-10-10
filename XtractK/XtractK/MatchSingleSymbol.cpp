#include "MatchSingleSymbol.h"

MatchSingleSymbol::MatchSingleSymbol(symbol_t symbol)
	: mSymbol{ symbol } 
{
}

bool MatchSingleSymbol::isMatching(symbol_t symbol) const
{ 
	return mSymbol == symbol; 
}

AbstractMatchSymbol* MatchSingleSymbol::clone() const 
{ 
	return new MatchSingleSymbol(mSymbol);
}