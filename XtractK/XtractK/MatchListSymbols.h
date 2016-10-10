//! \file MatchListSymbols.h
//!
//! \brief Définition de la classe MatchListSymbols.
//! \details Ce fichier fait partie du laboratoire 1 donné dans le cadre du cours 
//! <a href="https://cours.etsmtl.ca/gpa789/" target="_blank">GPA789 Analyse et conception orientées objet</a>.
//!
//! \version 1.0
//!
//! \author Tony Wong, Ph.D.\n
//!		Département de génie de production automatisée\n
//!		École de technologie supérieure\n
//!		tony.wong@etsmtl.ca
//! \author	JC Demers
//!
//! \date 2000-2016
//! \copyright Copyleft 2000-2016

#ifndef MATCH_LIST_SYMBOLS_H
#define MATCH_LIST_SYMBOLS_H

#include "AbstractMatchSymbol.h"
#include <list>
#include <initializer_list>

using namespace std;

//! \brief		Classe représentant l'acceptation d'un symbole parmi un 
//!				ensemble de symboles.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe hérite de la classe AbstractMatchSymbol et permet
//!				l'acceptation d'un symbole parmi un ensemble de symboles. Le 
//!				symbole accepté doit être identique à l'un des symboles
//!				présent dans l'ensemble de référence.
//!
//!				L'ensemble des symboles de référence doit être spécifié à la 
//!				déclaration de la classe et ne peut être modifié.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class MatchListSymbols : public AbstractMatchSymbol
{
public:
	MatchListSymbols() = delete;
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste de symboles.
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchListSymbols(list<symbol_t> const & symbols);
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste d'initialisatoin de symboles
	//! (initializer_list).
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchListSymbols(initializer_list<symbol_t> const & symbols);
	//! Destructeur.
	virtual ~MatchListSymbols() = default;

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