//! \file MatchAllSymbols.h
//!
//! \brief Définition de la classe MatchAllSymbols.
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

#ifndef MATCH_ALL_SYMBOLS_H
#define MATCH_ALL_SYMBOLS_H

#include "AbstractMatchSymbol.h"

//! \brief		Classe représentant l'acceptation de tous les symboles.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe hérite de la classe AbstractMatchSymbol et permet
//!				l'acceptation de tous les symboles.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class MatchAllSymbols : public AbstractMatchSymbol
{
public:
	//! Constructeur par défaut.
	MatchAllSymbols() = default;
	//! Destructeur par défaut.
	virtual ~MatchAllSymbols() = default;

	//! La fonction d'acceptation retourne toujours vrai.
	virtual bool isMatching(symbol_t symbol) const override;

	// Retourne une nouvelle copie de l'instance courante.
	virtual AbstractMatchSymbol* clone() const override;
};


#endif