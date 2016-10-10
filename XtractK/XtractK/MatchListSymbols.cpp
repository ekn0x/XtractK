#include "MatchListSymbols.h"

#include <algorithm>
using namespace std;


MatchListSymbols::MatchListSymbols(list<symbol_t> const & symbols)
	: mSymbols{ symbols }
{
}

MatchListSymbols::MatchListSymbols(initializer_list<symbol_t> const & symbols)
	: mSymbols{ symbols } 
{
}

bool MatchListSymbols::isMatching(symbol_t symbol) const
{ 
	return find(mSymbols.begin(), mSymbols.end(), symbol) != mSymbols.end();
}

AbstractMatchSymbol* MatchListSymbols::clone() const 
{ 
	return new MatchListSymbols(mSymbols); 
}