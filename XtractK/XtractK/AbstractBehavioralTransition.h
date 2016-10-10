//! \file AbstractBehavioralTransition.h
//!
//! \brief Définition de la classe AbstractBehavioralTransition.
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

#ifndef ABSTRACT_BEHAVIORAL_TRANSITION_H
#define ABSTRACT_BEHAVIORAL_TRANSITION_H


#include "Transition.h"

class FiniteStateMachine;
class AbstractBehavioralState;


//! \brief		Classe représentant les transitions d'un automate 
//!				comportemental à états-finis.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour toutes 
//!				transition de l'ACEF. L'interface commune réside principalement dans 
//!				les fonctions de travail.
//!
//!				Chaque transition possède maintenant 2 fonctions permettant de définir 
//!				un comportement particulier pour des situations particulières. 
//!				C'est la classe FiniteStateMachine qui s'ocuupe d'appeler 
//!				ces fonctions au bon moment. Ces tâches supplémentaires sont :
//!				 - reset (fonction virtuelle pure) : cette fonction est appelée 
//!					au démarrage de l'automate, c'est à dire lorsque la 
//!					fonction start est appelée.
//!				 - process (fonction virtuelle pure) : cette fonction est appelée 
//!					à chaque traitement de symbole lorsqu'une transition 
//!					est effective par la fonction processSymbol de l'automate
//!
//!				Cette classe est virtuelle pure et ne peut être instanciée.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class AbstractBehavioralTransition : public Transition
{
	friend FiniteStateMachine;
	friend AbstractBehavioralState;

public:
	AbstractBehavioralTransition() = delete;
	//! Constructeur. Il est nécessaire de donner un nom, 
	//! l'état suivant et la condition.
	AbstractBehavioralTransition(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState);
	//! Destructeur par défaut.
	virtual ~AbstractBehavioralTransition() = default;

protected:
	//! Fonction de réinitialisation de la transition.
	virtual void reset() = 0;
	//! Fonction d'action lorsque la transition courante 
	//! est effective et traite un nouveau symbole.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) = 0;
};


#endif // ABSTRACT_BEHAVIORAL_TRANSITION_H