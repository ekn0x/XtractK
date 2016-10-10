//! \file Transition.h
//!
//! \brief Définition de la classe Transition.
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

#ifndef TRANSITION_H
#define TRANSITION_H

#include "Symbol.h"

#include <string>
using namespace std;

class AbstractMatchSymbol;
class State;


//! \brief		Classe représentant les transitions d'un automate à états-finis.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour toutes 
//!				les transitions de l'AEF. L'interface commune réside 
//!				principalement dans la gestion de l'état suivant et de 
//!				la condition de transition.
//!
//!				Chaque transition possède :
//!				 - un nom (les noms peuvent être répétés)
//!				 - l'état suivant
//!				 - la condition de transition
//!
//!				C'est le constructeur qui permet de définir de façon immuable 
//!				tous ces paramètres. 
//!
//!				Les conditions sont exprimées par la classe AbstractMatchSymbol
//!				et ses déscendants. Lorsqu'une condition (un item 
//!				_MatchSymbol_) est passée au constructeur, la transition 
//!				devient propriétaire de la condition.
//!				Ainsi, c'est lors de la suppression des transitions que les 
//!				conditions sont libérées. Il est important de ne pas libérer la 
//!				mémoire des objets `AbstractMatchSymbol` ailleurs dans le 
//!				programme. Il est d'un mauvais usage d'accéder aux conditions 
//!				après qu'elles aient été assignées (ajoutées) à un transition. 
//!				Chaque condition doit être créée dynamiquement et assignée 
//!				à un seul état. Deux conditions identiques appliqué à des 
//!				transitions différentes requiert deux objets _condition_ 
//!				différents. L'assignation à deux transition 
//!				produira une erreure de désallocation de la mémoire.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class Transition
{
public:
	Transition() = delete;
	//! Constructeur. Il est nécessaire de donner un nom, l'état suivant et 
	//! la condition.
	Transition(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState);
	//! Destructeur. Libère la condition de la transition.
	virtual ~Transition();

	//! Retourne le nom de la transition.
	string const & name() const { return mName; }
	//! Retourne le nom de la transition.
	string name() { return mName; }
	//! Retourne l'état suivant de la transition.
	State* nextState() const { return mNextState; }
	//! Fonction évaluant si la transition est effective 
	//! pour un symbole donné. 
	bool isTransiting(symbol_t symbol) const;

private:
	string mName;
	AbstractMatchSymbol * mMatchSymbol;
	State * mNextState;

};


#endif // TRANSITION_H