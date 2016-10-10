//! \file StateCounter.h
//!
//! \brief Définition de la classe StateCounter.
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

#ifndef STATE_COUNTER_H
#define STATE_COUNTER_H


#include "AbstractBehavioralState.h"
#include <cstdint>

//! \brief		Classe représentant des états qui cumulent des informations sur
//!				le nombre de fois que leurs fonctions comportementales sont 
//!				appelées.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour tous 
//!				les états de l'ACEF qui désire produire certaines statistiques. 
//!				L'interface commune est la gestion des trois fonctions 
//!				d'opération.
//!
//!				On retrouve trois types d'information :
//!				 - enterCount : le nombre de fois que l'état courant est entré 
//!					dans cet état
//!				 - doCount : le nombre de fois que l'état courant a traité un 
//!					symbole
//!				 - exitCount : le nombre de fois que l'état courant a quiité
//!					cet état
//!
//!				Toutes les fonctions abstraites de la classe parent ont été 
//!				réimplémentées. Il est donc possible d'instancier un objet de 
//!				cette classe.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class StateCounter : public AbstractBehavioralState
{
public:
	StateCounter() = delete;
	//! Constructeur. Il est nécessaire de donner un nom et l'état acceptant à 
	//! la création d'un état.
	StateCounter(const string & name, bool accepting = false);
	//! Destructeur par défaut.
	virtual ~StateCounter() = default;

	//! Retourne le nombre de fois que l'état courant est entré dans cet état.
	uint32_t enterCount() const { return mEnterCount; }
	//! Retourne le nombre de fois que l'état courant a traité un symbole.
	uint32_t doCount() const { return mDoCount; }
	//! Retourne le nombre de fois que l'état courant a quiité cet état
	uint32_t exitCount() const { return mExitCount; }

protected:
	//! Surcharge de la fonction parent. Remet les compteurs à 0.
	virtual void reset() override;
	//! Surcharge de la fonction virutelle pure parent. Incrémente le compteur.
	virtual void entering(symbol_t prevSymbol, symbol_t curSymbol) override;
	//! Surcharge de la fonction virutelle pure parent. Incrémente le compteur.
	virtual void doing(symbol_t prevSymbol, symbol_t curSymbol) override;
	//! Surcharge de la fonction virutelle pure parent. Incrémente le compteur.
	virtual void exiting(symbol_t prevSymbol, symbol_t curSymbol) override;

private:
	uint32_t mEnterCount;
	uint32_t mDoCount;
	uint32_t mExitCount;
};


#endif // STATE_COUNTER_H