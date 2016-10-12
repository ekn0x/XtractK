//! \file MatchListSymbols.h
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
#include <list>
#include <initializer_list>

using namespace std;

class MatchRangeSymbols : public AbstractMatchSymbol
{
public:
	MatchRangeSymbols() = delete;
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste de symboles.
	//!	L'ensemble des symboles ne peut �tre modifi� par la suite. 
	MatchRangeSymbols(list<symbol_t> const & symbols);
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste d'initialisatoin de symboles
	//! (initializer_list).
	//!	L'ensemble des symboles ne peut �tre modifi� par la suite. 
	MatchRangeSymbols(initializer_list<symbol_t> const & symbols);
	//! Destructeur.
	virtual ~MatchRangeSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est inclu dans la liste des symboles
	//! de r�f�rence. La liste des symboles de r�f�rence est celui d�finie
	//! lors de la d�finition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;

protected:
	list<symbol_t> mSymbols;
};

#endif