//! \file TransitionCounter.h
//!
//! \brief Définition de la classe TransitionCounter.
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

#ifndef TRANSITION_COUNTER_H
#define TRANSITION_COUNTER_H


#include "AbstractBehavioralTransition.h"
#include <cstdint>


//! \brief		Classe représentant des transitions qui cumulent des informations sur
//!				le nombre de fois que leurs fonctions comportementales sont 
//!				appelées.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour toutes 
//!				les transitions de l'ACEF qui désire produire certaines statistiques. 
//!				L'interface commune est la gestion des deux fonctions 
//!				d'opération.
//!
//!				On retrouve une information supplémentaire :
//!				 - count : le nombre de fois que la transition a été effective
//!
//!				Toutes les fonctions abstraites de la classe parent ont été 
//!				réimplémentées. Il est donc possible d'instancier un objet de 
//!				cette classe.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class TransitionCounter : public AbstractBehavioralTransition
{
public:
	TransitionCounter() = delete;
	//! Constructeur. Il est nécessaire de donner un nom, l'état suivant et 
	//! la condition.
	TransitionCounter(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState);
	//! Destructeur par défaut.
	virtual ~TransitionCounter() = default;

	//! Retourne le nombre de fois que la transition a été effective 
	//! et qu'elle a traité un symbole.
	uint32_t count() const { return mCount; }

protected:
	//! Surcharge de la fonction virtuelle pure parent. Remet le compteur à 0.
	virtual void reset() override;
	//! Surcharge de la fonction virutelle pure parent. Incrémente le compteur.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;

protected:
	uint32_t mCount;
	
};


#endif // TRANSITION_COUNTER_H