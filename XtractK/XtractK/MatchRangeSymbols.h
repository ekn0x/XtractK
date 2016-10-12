//! \file MatchRangeSymbols.h
//!
//! \brief D�finition de la classe MatchListSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		�tudiants
//!		D�partement de g�nie de production automatis�e\n
//!		�cole de technologie sup�rieure\n
//!

#ifndef MATCH_RANGE_SYMBOLS_H
#define MATCH_RANGE_SYMBOLS_H

#include "AbstractMatchSymbol.h"

using namespace std;

class MatchRangeSymbols : public AbstractMatchSymbol
{
public:
	MatchRangeSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	//!	Les symboles de debut et de fin ne peuvent �tre modifi�s par la suite. 
	MatchRangeSymbols(symbol_t const first, symbol_t const last);
	//! Destructeur.
	virtual ~MatchRangeSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de r�f�rence. La suite des symboles de r�f�rence est celle d�finie
	//! lors de la d�finition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	symbol_t mFirst;
	symbol_t mLast;
};

#endif