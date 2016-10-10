//! \file TransitionNewConstant.h
//!
//! \brief D�finition de la classe TransitionNewCosntant.
//!
//! \version 1.0
//!
//! \author Alex H.Lamarche
//!

#ifndef TRANSITION_NEW_CONSTANT_H
#define TRANSITION_NEW_CONSTANT_H


#include "TransitionOStream.h"

#include "FSMFileStatistics.h"


//! \brief		Transition sp�cifique concernant l'entr�e 
//!				dans une nouvelle constant.
//! \details	Cette classe fait partie de la solution Xtractk. 
//! 
//!				Elle correspond � l'impl�mentation de la transition du m�me 
//!				nom sur le sch�ma de conception pr�sent� 
//!				
//!				Consiste en une surcharge de la fonction de traitement afin 
//!				d'afficher :
//!				 - num�ro de ligne
//!				 - saut de ligne
//!				 - symbole pr�c�dent
//!				 - symbole courant
//! 
//!				Cette classe requiert le num�ro de ligne du fichier pour l'
//!				affichage � r�aliser. On obtient cette information en passant 
//!				une r�f�rence � l'automate des statistiques du fichier. Ainsi, 
//!				il est possible d'avoir acc�s en tout temps au num�ro de ligne 
//!				courant.
//!

class TransitionNewConstant : public TransitionOStream
{
public:
	TransitionNewConstant() = delete;
	//! Constructeur requ�rant le nom, la condition, l'�tat suivant, la 
	//! source des num�ros de ligne, le nombre de 0 pour le formattage 
	//! du num�ro de ligne et le flux de sortie. 
	TransitionNewConstant(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, FSMFileStatistics const & fileStatistics, int linePaddingLength, ostream * stream = &cout);
	//! Destructeur par d�faut.
	virtual ~TransitionNewConstant() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;

private:
	FSMFileStatistics const & mFileStatistics;
	int mLinePaddingLength;
};

#endif // TRANSITION_NEW_CONSTANT_H
