//! \file AbstractBehavioralState.h
//!
//! \brief Définition de la classe AbstractBehavioralState.
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

#ifndef ABSTRACT_BEHAVIORAL_STATE_H
#define ABSTRACT_BEHAVIORAL_STATE_H

#include "State.h"
class FiniteStateMachine;


//! \brief		Classe représentant les états d'un automate comportemental à 
//!				états-finis.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour tous 
//!				états de l'ACEF. L'interface commune réside principalement dans 
//!				les fonctions de travail.
//!
//!				Chaque état possède maintenant 4 fonctions permettant de définir 
//!				un comportement particulier pour des situations particulières. 
//!				C'est la classe FiniteStateMachine qui s'ocuupe d'appeler 
//!				ces fonctions au bon moment. Ces tâches supplémentaires sont :
//!				 - reset : cette fonction est appelée au démarrage de 
//!					l'automate, c'est à dire lorsque la fonction start est appelée.
//!				 - entering (fonction virtuelle pure) : cette fonction est appelée 
//!					lors d'une transition vers l'état courant (après la transition). 
//!				 - doing (fonction virtuelle pure) : cette fonction est appelée 
//!					à chaque traitement de symbole de la part de l'automate avec la 
//					fonction processSymbol (c'est l'objet de l'état courant qui est appelé). 
//!				 - exiting (fonction virtuelle pure) : cette fonction est appelée 
//!					lors d'une transition vers un nouvel état (l'état courant appel cette 
//!					fonction juste avant la transition vers le nouvel état). 
//!
//!				Cette classe est virtuelle pure et ne peut être instanciée.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class AbstractBehavioralState : public State
{
	friend FiniteStateMachine;

public:
	AbstractBehavioralState() = delete;
	//! Constructeur. Il est nécessaire de donner un nom et l'état acceptant à 
	//! la création d'un état.
	AbstractBehavioralState(const string & name, bool accepting = false);
	//! Destructeur par défaut.
	virtual ~AbstractBehavioralState() = default;

protected:
	//! Fonction de réinitialisation de l'état.
	virtual void reset();
	//! Fonction d'action lorsque l'état courant devient cet état.
	virtual void entering(symbol_t prevSymbol, symbol_t curSymbol) = 0;
	//! Fonction d'action lorsque l'état courant traite un nouveau symbole.
	virtual void doing(symbol_t prevSymbol, symbol_t curSymbol) = 0;
	//! Fonction d'action lorsque l'état courant quitte cet état.
	virtual void exiting(symbol_t prevSymbol, symbol_t curSymbol) = 0;
};

#endif // ABSTRACT_BEHAVIORAL_STATE_H