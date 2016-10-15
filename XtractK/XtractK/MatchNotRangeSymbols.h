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

#ifndef MATCH_NOT_RANGE_SYMBOLS_H
#define MATCH_NOT_RANGE_SYMBOLS_H

#include "MatchRangeSymbols.h"

class Range;

using namespace std;

class MatchNotRangeSymbols : public MatchRangeSymbols
{
public:
	MatchNotRangeSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	//!	Les symboles de debut et de fin ne peuvent �tre modifi�s par la suite. 
	MatchNotRangeSymbols(symbol_t const first, symbol_t const last);
	//! Destructeur.
	virtual ~MatchNotRangeSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de r�f�rence. La suite des symboles de r�f�rence est celle d�finie
	//! lors de la d�finition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;
};

#endif
