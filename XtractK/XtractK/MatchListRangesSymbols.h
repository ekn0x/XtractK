//! \file MatchListRangesSymbols.h
//!
//! \brief D�finition de la classe MatchListRangeSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		�tudiants
//!		D�partement de g�nie de production automatis�e\n
//!		�cole de technologie sup�rieure\n
//!

#ifndef MATCH_LIST_RANGES_SYMBOLS_H
#define MATCH_LIST_RANGES_SYMBOLS_H

#include "MatchRangeSymbols.h"
#include <list>
#include <initializer_list>

using namespace std;

class MatchListRangesSymbols : public AbstractMatchSymbol
{
public:
	MatchListRangesSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	//!	Les symboles de debut et de fin ne peuvent �tre modifi�s par la suite. 
	MatchListRangesSymbols(symbol_t const first, symbol_t const last);
	//! Destructeur.
	virtual ~MatchListRangesSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de r�f�rence. La suite des symboles de r�f�rence est celle d�finie
	//! lors de la d�finition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	list<MatchRangeSymbols> mRangeList;
};

#endif