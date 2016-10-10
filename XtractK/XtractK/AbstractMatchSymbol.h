//! \file AbstractMatchSymbol.h
//!
//! \brief Définition de la classe AbstractMatchSymbol.
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

#ifndef ABSTRACT_MATCH_SYMBOL_H
#define ABSTRACT_MATCH_SYMBOL_H

#include "Symbol.h"

//! \brief		Classe abstraite représentant l'acceptation d'un symbole.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour tous 
//!				les types de symbole à manipuler. Selon l'implémentation des 
//!				fonctions requises, il est possible de créer des règles simples 
//!				ou plus complexes permettant d'accepter ou non un symbole. 
//!
//!				Cette classe sert aux différents objets de transitions afin de 
//!				déterminer si une transition est effective ou non (voir la 
//!				classe Transition).
//!
//!				Par exemple, il est possible de créer des classes acceptant un 
//!				symbole spécifique ou un symbole différent de ce symbole. 
//!				Il est aussi possible de créer des ensembles de symboles homogènes 
//!				ou hétéroclites.
//!				
//!				Cette classe est virtuelle pure et ne peut être instanciée.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class AbstractMatchSymbol
{
public:
	//! Constructeur par défaut.
	AbstractMatchSymbol() = default;
	//! Destructeur par défaut.
	virtual ~AbstractMatchSymbol() = default;

	//! La fonction isMatching est la fonction d'acceptation de l'AEF. Cette fonction 
	//! permet de déterminer si un symbole est accepté ou non. Cette acceptation est 
	//! principalement utilisé dans une transition afin de savoir si une transition
	//! est effective ou non.
	//!
	//! Cette fonction est virtuelle pure et doit être redéfinie.
	virtual bool isMatching(symbol_t symbol) const = 0;

	//! Cette fonction permet d'instancier un objet identique à l'objet courant.
	//! Le nouvel objet est alloué dynamiquement et devient la propriété du récepteur.
	//! Entre d'autres termes, l'allocation dynamique de la mémoire doit être gérée 
	//! explicitement par un mécanisme externe.
	//!
	//! Cette fonction est virtuelle pure et doit être redéfinie.
	virtual AbstractMatchSymbol* clone() const = 0;
};


#endif