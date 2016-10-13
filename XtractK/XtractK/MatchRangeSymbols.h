//! \file MatchRangeSymbols.h
//!
//! \brief Définition de la classe MatchRangeSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		Étudiants
//!		Département de génie de production automatisée\n
//!		École de technologie supérieure\n
//!

#ifndef MATCH_RANGE_SYMBOLS_H
#define MATCH_RANGE_SYMBOLS_H

#include "AbstractMatchSymbol.h"
#include "Range.h"

using namespace std;

class MatchRangeSymbols : public AbstractMatchSymbol
{
public:
	MatchRangeSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	//!	Les symboles de debut et de fin ne peuvent être modifiés par la suite. 
	MatchRangeSymbols(symbol_t const first, symbol_t const last);
	//! Destructeur.
	virtual ~MatchRangeSymbols();

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de référence. La suite des symboles de référence est celle définie
	//! lors de la définition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	Range * rangeValues;
};

#endif
