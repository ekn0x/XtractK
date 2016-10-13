//! \file MatchListRangesSymbols.h
//!
//! \brief Définition de la classe MatchListRangeSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		Étudiants
//!		Département de génie de production automatisée\n
//!		École de technologie supérieure\n
//!

#ifndef MATCH_LIST_RANGES_SYMBOLS_H
#define MATCH_LIST_RANGES_SYMBOLS_H

#include "MatchRangeSymbols.h"
#include <list>
#include <initializer_list>

class MatchRangeSymbols;

using namespace std;

class MatchListRangesSymbols : public AbstractMatchSymbol
{
public:
	MatchListRangesSymbols() = delete;
	//! Ce constructeur utilise une suite de symboles.
	//!	Les symboles de debut et de fin ne peuvent être modifiés par la suite. 
	MatchListRangesSymbols(symbol_t const first, symbol_t const last);
	//! Constructeurs à l'aide de liste
	//! List non initialisé
	MatchListRangesSymbols(initializer_list<MatchRangeSymbols> const & rangeList);
	//! Liste deja initialiser
	MatchListRangesSymbols(list<MatchRangeSymbols> const & rangeList);
	
	//! Destructeur.
	virtual ~MatchListRangesSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la suite de symboles
	//! de référence. La suite des symboles de référence est celle définie
	//! lors de la définition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	list<MatchRangeSymbols> mRangeList;
};

#endif
