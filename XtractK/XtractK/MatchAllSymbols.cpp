#include "MatchAllSymbols.h"

bool MatchAllSymbols::isMatching(symbol_t symbol) const
{ 
	return true; 
}

AbstractMatchSymbol* MatchAllSymbols::clone() const 
{ 
	return new MatchAllSymbols(); 
}
