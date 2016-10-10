// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GPA789 Analyse et conception orientées objet
//
// Laboratoire 1 : XtractC
//
// MatchListSymbols.cpp
//
// Tony Wong, Ph.D.
// Département de génie de production automatisée
#include "MatchNotListSymbols.h"

MatchNotListSymbols::MatchNotListSymbols(list<symbol_t> const & symbols)
	: MatchListSymbols{ symbols } 
{ 
}

MatchNotListSymbols::MatchNotListSymbols(initializer_list<symbol_t> const & symbols)
	: MatchListSymbols{ symbols } 
{ 
}

bool MatchNotListSymbols::isMatching(symbol_t symbol) const
{ 
	return !MatchListSymbols::isMatching(symbol); 
}

AbstractMatchSymbol* MatchNotListSymbols::clone() const 
{ 
	return new MatchNotListSymbols(mSymbols); 
}