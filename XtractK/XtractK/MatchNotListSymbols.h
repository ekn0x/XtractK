//! \file MatchNotListSymbols.h
//!
//! \brief Définition de la classe MatchNotListSymbols.
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

#ifndef MATCH_NOT_LIST_SYMBOLS_H
#define MATCH_NOT_LIST_SYMBOLS_H

#include "MatchListSymbols.h"

//! \brief		Classe représentant l'acceptation d'un symbole différent parmi 
//!				un ensemble de symboles.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe hérite de la classe MatchListSymbols et permet
//!				l'acceptation d'un symbole différent parmi un ensemble de 
//!				symboles. Le symbole accepté doit être différent de tous les 
//!				symboles présents dans l'ensemble de référence.
//!
//!				L'ensemble des symboles de référence doit être spécifié à la 
//!				déclaration de la classe et ne peut être modifié.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class MatchNotListSymbols : public MatchListSymbols
{
public:
	MatchNotListSymbols() = delete;
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste de symboles.
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchNotListSymbols(list<symbol_t> const & symbols);
	//! Constructeur initialisant l'ensemble des symboles de comparaison. 
	//! Ce constructeur utilise une liste d'initialisatoin de symboles
	//! (initializer_list).
	//!	L'ensemble des symboles ne peut être modifié par la suite. 
	MatchNotListSymbols(initializer_list<symbol_t> const & symbols);
	//! Destructeur.
	virtual ~MatchNotListSymbols() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est différent de tous ceux de la liste 
	//! des symboles de référence. La liste des symboles de référence est 
	//! celui définie lors de la définition de l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;
};

#endif