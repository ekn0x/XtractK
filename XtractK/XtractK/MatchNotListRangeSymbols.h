//! \file MatchNotRangeSymbols.h
//!
//! \brief D�finition de la classe MatchRangeSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		�tudiants
//!		D�partement de g�nie de production automatis�e\n
//!		�cole de technologie sup�rieure\n
//!

#ifndef MATCH_NOT_LIST_RANGE_SYMBOLS_H
#define MATCH_NOT_LIST_RANGE_SYMBOLS_H

#include "MatchListRangeSymbols.h"

class Range;

using namespace std;

class MatchNotListRangeSymbols : public MatchListRangeSymbols
{
public:
	MatchNotListRangeSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	MatchNotListRangeSymbols(list<Range> const & listRange);
	//!	Les symboles de debut et de fin ne peuvent �tre modifi�s par la suite. 
	MatchNotListRangeSymbols(initializer_list<Range> const & listRange);
	//! Destructeur.
	virtual ~MatchNotListRangeSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de r�f�rence. La suite des symboles de r�f�rence est celle d�finie
	//! lors de la d�finition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;
};

#endif
