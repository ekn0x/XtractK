//! \file FiniteStateMachine.h
//!
//! \brief Définition de la classe FiniteStateMachine.
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

#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include "Symbol.h"
#include <list>
using namespace std;

class State;
class Transition;


//! \brief		Classe représentant au automate à états-finis. Cet automate gère 
//!				les AEF et ACEF.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Une présentation formelle des automates est présentée dans cette 
//!				section : \ref fsm
//!
//!				Cette classe gère les deux types d'automates présentés 
//!				sans distinction (qu'il soit comportemental ou non). Il est 
//!				intéressant de constater que n'importe quel type d'état 
//!				(`State` ou `AbstractBehavioralState`) et n'importe quel 
//!				type de transition (`Transition` ou 
//!				`AbstractBehavioralTransition`) peuvent être utilisés 
//!				simultanément dans le même automate. Les processus de 
//!				résolution interne de l'automate déterminent quel sont les 
//!				types de chaque état et chaque transition afin d'appeller 
//!				les fonctions comportementales le cas échéant.
//!
//!				La séquence suivante montre 
//!				comment utiliser l'automate :
//!              -# création des états
//!				 -# création des transitions (en utilisant les états définis)
//!				 -# ajout des transitions aux états déclencheurs (appelés aussi 
//!					états possesseurs)
//!				 -# ajout des états à l'automate
//!				 -# assignation de l'état initial
//!				 -# démarrage de l'automate
//!				 -# traitement des symboles par l'automate
//!				 -# arrêt de l'automate
//!				\code{.cpp}
//!				// Étape 1 : création des états
//!				State * myState1 = new State("My First State", true);
//!				State * myState2 = new State("My Second State", false);
//!
//!				// Étape 2 : création des transitions
//!				Transition * myTransition = new TransitionCounter("Valid *", new MatchSingleSymbol('*'), myState2);
//! 
//!				// Étape 3 : ajout des transitions aux états
//!				myState1->addTransition(myTransition);
//!
//!				// Étape 4 : ajout des états à l'automate
//!				FiniteStateMachine myMachine;
//!				myMachine.addState(myState1);
//!				myMachine.addState(myState2);
//!
//!				// Étape 5 : assignation de l'état initial
//!				myMachine.setInitialState(myState1);
//!
//!				// Étape 6 : démarrage de l'automate
//!				myMachine.start();
//!
//!				// Étape 7 : traitement des symboles par l'automate
//!				// ...
//!				myMachine.processSymbol('*');
//!				// ...
//!
//!				// Étape 8 : arrêt de l'automate
//!				bool acceptingState = myMachine.stop();
//!				\endcode
//!
//!				Les fonctions `addState`, `setInitialState` et `setStream` 
//!				permettent de définir la structure de l'automate.
//!
//!				Les fonctions `start`, `processSymbol` et `stop` permettent 
//!				de gérer l'exécution de l'automate.
//!
//!				Les fonctions `isRunning` et `currentStateName` permettent 
//!				de questionner l'automate sur son opération.
//!
//!				Les fonctions `setNoStateName` et `noStateName` offrent une 
//!				gestion personnalisé de la chaîne de sortie de la fonction 
//!				currentStateName lorque l'état courant n'est pas défini. 
//!				Par défaut, la chaîne de caractères retournée est 
//!				`"-no current state-"`. Il est possible de retourner 
//!				une chaîne de caractères personnalisée pour cette situation.
//!
//!				L'automate est propriétaires des états qui y sont ajoutés. 
//!				C'est au moment de la suppression de l'automate que les 
//!				états sont libérées. Il est important de ne pas libérer la 
//!				mémoire des objets `State` ailleurs dans le programme. Il est d'un 
//!				mauvais usage d'accéder aux états après qu'ils aient été 
//!				assignées (ajoutées) à l'automate. Chaque état doit être créé
//!				dynamiquement et assigné à un seul automate. L'assignation à deux automates 
//!				produira une erreure de désallocation de mémoire.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class FiniteStateMachine
{
public:
	//! Constructeur par défaut.
	FiniteStateMachine();
	FiniteStateMachine(FiniteStateMachine const &) = delete;
	FiniteStateMachine(FiniteStateMachine const &&) = delete;
	FiniteStateMachine& operator=(FiniteStateMachine const &) = delete;
	FiniteStateMachine& operator=(FiniteStateMachine const &&) = delete;
	//! Destructeur par défaut.
	virtual ~FiniteStateMachine();

	//! Insère un état à l'automate. Si l'état existe déjà, la fonction 
	//!	retourne sans rien faire. Si le paramètre est `nullptr` une 
	//! exception `std::invalid_argument` est générée.
	void addState(State * state);
	//! Détermine l'état initial. Si l'état spécifié n'existe pas ou si 
	//! le paramètre est `nullptr` une exception 
	//! `std::invalid_argument` est générée.
	void setInitialState(State * initState);
	// Permet de spécifier le flux de sortie pour toutes les transitions 
	//! de types TransitionOStream. Si l'automate ne possède aucune de 
	//! ces transitions, cette fonction ne fait rien.
	void setStream(ostream * stream);

	//! Amorce le démarrage de l'automate. Si l'automate ne possède 
	//! aucun état ou si l'état initiale n'est pas défini, une exception 
	//! `std::logic_error` est générée. Si L'automate est en opération, 
	//! l'automate est d'abord arrêté avant d'être réinitialisé et redémaré.
	void start();
	//! Effectu le traitement d'un symbole. Cette fonction gère les 
	//! différents d'exécution
	void processSymbol(symbol_t curSymbol);
	//! Arrête l'automate. Retourne si le dernier état était un 
	//! état acceptant.
	bool stop();

	//! Retourne si l'automate est en opération (_started_).
	bool isRunning() const { return mRunning; }

	//! Retourne le nom de l'état courant. Si aucun état n'est spécifié, 
	//! c'est `noStateName` qui est retourné.
	string currentStateName(void) const;
	//! Permet de spécifier un `noStateName` spécifique.
	static void setNoStateName(string const & name) { mNoStateName = name; }
	//! Retourne le `noStateName`.
	static string const & noStateName() { return mNoStateName; }

private:
	static string mNoStateName;

	symbol_t mPreviousSymbol;
	bool mRunning;
	State* mInitialState;
	State* mCurrentState;
	list<State*> mStates;

	void processBehavioralTransition(Transition * transition, symbol_t curSymbol);
	void exitCurrentBehavioralState(symbol_t curSymbol);
	void enterProcessCurrentBehavioralState(symbol_t curSymbol);
	void processCurrentBehavioralState(symbol_t curSymbol);
	void resetBehavioralStates();
	void resetBehavioralTransitions();

	static void deleteState(State * & state);
};


#endif // FINITE_STATE_MACHINE_H