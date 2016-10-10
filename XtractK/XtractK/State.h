//! \file State.h
//!
//! \brief Définition de la classe State.
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

#ifndef STATE_H
#define STATE_H

#include <string>
#include <list>
using namespace std;

#include "Symbol.h"

class Transition;
class FiniteStateMachine;

//! \brief		Classe représentant les états d'un automate à états-finis.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour tous 
//!				états de l'AEF. L'interface commune réside principalement dans 
//!				la gestion des transitions.
//!
//!				Chaque état possède un nom en plus de son état acceptant. Cet 
//!				état acceptant permettra de valider si le déroulement du 
//!				traitement valide la chaîne de symboles donnés.
//!
//!				La fonction addTransition permet d'ajouter autant de 
//!				transition que nécessaire. C'est la fonction isTransiting qui 
//!				valide si l'état courant passe vers un nouvel état.
//!
//!				Tous les états sont propriétaires des transitions qui leurs 
//!				sont ajoutées. Ainsi, c'est lors de la suppression des états que les 
//!				transitions sont libérées. Il est important de ne pas libérer la 
//!				mémoire des objets `Transition` ailleurs dans le programme. Il est d'un 
//!				mauvais usage d'accéder aux transitions après qu'elles aient été 
//!				assignées (ajoutées) à un état. Chaque transition doit être créée 
//!				dynamiquement et assignée à un seul état. L'assignation à deux états 
//!				produira une erreure de désallocation de mémoire.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class State
{
	friend FiniteStateMachine;

public:
	State() = delete;
	//! Constructeur. Il est nécessaire de donner un nom et l'état acceptant à 
	//! la création d'un état.
	State(string const & name, bool accepting = false);
	//! Destructeur. Libère toutes les transitions de l'état.
	virtual ~State();

	//! Ajoute une transition à l'état. La transition passée devient la 
	//! propriété de cet état. L'ordre des insertions est important 
	//! car il détermine l'ordre des résolution.
	void addTransition(Transition * transition);
	//! Retourne le nombre de transition que possède un état.
	unsigned int transitionCount() const { return mTransitions.size(); }

	//! Retourne le nom de l'état.
	string const & name() const { return mName; }
	//! Retourne le nom de l'état.
	string name() { return mName; }
	//! Retourne si l'état est un état acceptant ou non.
	bool isAccepting() { return mAccepting; }

protected:
	//! Fonction évaluant si l'état courant passe de cet état vers un 
	//! prochain état. Cette fonction retourne nullptr lorsqu'aucune 
	//! transition n'est effective. Si la transition est effective, 
	//! un pointeur vers cette transition est retourné.
	Transition * isTransiting(symbol_t curSymbol);

protected:
	//! La liste de transition que possède l'état.
	list<Transition*> mTransitions;

private:
	string mName;
	bool mAccepting;

	static void deleteTransition(Transition * & transition);
};


#endif // STATE_H
