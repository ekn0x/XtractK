#include "MatchNotSingleSymbol.h"

MatchNotSingleSymbol::MatchNotSingleSymbol(symbol_t symbol)
	: MatchSingleSymbol{ symbol }
{
}

bool MatchNotSingleSymbol::isMatching(symbol_t symbol) const
{ 
	return !MatchSingleSymbol::isMatching(symbol);
}

AbstractMatchSymbol* MatchNotSingleSymbol::clone() const 
{ 
	return new MatchNotSingleSymbol(mSymbol); 
}