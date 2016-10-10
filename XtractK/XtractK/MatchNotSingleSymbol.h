//! \file MatchNotSingleSymbol.h
//!
//! \brief Définition de la classe MatchNotSingleSymbol.
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

#ifndef MATCH_NOT_SINGLE_SYMBOL_H
#define MATCH_NOT_SINGLE_SYMBOL_H

#include "MatchSingleSymbol.h"

//! \brief		Classe représentant l'acceptation d'un symbole différent à un 
//!				symbole spécifique.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe hérite de la classe MatchSingleSymbol et permet
//!				l'acceptation d'un symbole unique. Le symbole accepté doit 
//!				être différent du symbole de référence.
//!
//!				Le symbole de référence doit être spécifié à la déclaration 
//!				de la classe et ne peut être modifié.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class MatchNotSingleSymbol : public MatchSingleSymbol
{
public:
	MatchNotSingleSymbol() = delete;
	//! Le constructeur requiert la définition du symbole de comparaison. Le 
	//!	symbole ne peut être modifié par la suite.
	MatchNotSingleSymbol(symbol_t symbol);
	//! Destructeur.
	virtual ~MatchNotSingleSymbol() = default;

	//! La fonction d'acceptation fait une comparaison du symbole et 
	//!	retourne vrai si ce dernier est différent au symbole de référence. Le 
	//! symbole de référence est celui défini lors de la définition de 
	//! l'instance.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;
};

#endif