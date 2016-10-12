//! \file MatchListSymbols.h
//!
//! \brief Définition de la classe MatchListSymbols.
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
#include <list>
#include <initializer_list>

using namespace std;

class MatchRangeSymbols : public AbstractMatchSymbol
{
public:
	MatchRangeSymbols() = delete;
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste de symboles.
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchRangeSymbols(list<symbol_t> const & symbols);
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste d'initialisatoin de symboles
	//! (initializer_list).
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchRangeSymbols(initializer_list<symbol_t> const & symbols);
	//! Destructeur.
	virtual ~MatchRangeSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la liste des symboles
	//! de référence. La liste des symboles de référence est celui définie
	//! lors de la définition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	list<symbol_t> mSymbols;
};

#endif