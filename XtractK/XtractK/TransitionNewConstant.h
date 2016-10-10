//! \file TransitionNewConstant.h
//!
//! \brief Définition de la classe TransitionNewCosntant.
//!
//! \version 1.0
//!
//! \author Alex H.Lamarche
//!

#ifndef TRANSITION_NEW_CONSTANT_H
#define TRANSITION_NEW_CONSTANT_H


#include "TransitionOStream.h"

#include "FSMFileStatistics.h"


//! \brief		Transition spécifique concernant l'entrée 
//!				dans une nouvelle constant.
//! \details	Cette classe fait partie de la solution Xtractk. 
//! 
//!				Elle correspond à l'implémentation de la transition du même 
//!				nom sur le schéma de conception présenté 
//!				
//!				Consiste en une surcharge de la fonction de traitement afin 
//!				d'afficher :
//!				 - numéro de ligne
//!				 - saut de ligne
//!				 - symbole précédent
//!				 - symbole courant
//! 
//!				Cette classe requiert le numéro de ligne du fichier pour l'
//!				affichage à réaliser. On obtient cette information en passant 
//!				une référence à l'automate des statistiques du fichier. Ainsi, 
//!				il est possible d'avoir accès en tout temps au numéro de ligne 
//!				courant.
//!

class TransitionNewConstant : public TransitionOStream
{
public:
	TransitionNewConstant() = delete;
	//! Constructeur requérant le nom, la condition, l'état suivant, la 
	//! source des numéros de ligne, le nombre de 0 pour le formattage 
	//! du numéro de ligne et le flux de sortie. 
	TransitionNewConstant(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, FSMFileStatistics const & fileStatistics, int linePaddingLength, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionNewConstant() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;

private:
	FSMFileStatistics const & mFileStatistics;
	int mLinePaddingLength;
};

#endif // TRANSITION_NEW_CONSTANT_H
