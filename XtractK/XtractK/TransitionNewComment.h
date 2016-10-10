//! \file TransitionNewComment.h
//!
//! \brief Définition de la classe TransitionNewComment.
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

#ifndef TRANSITION_NEW_COMMENT_H
#define TRANSITION_NEW_COMMENT_H


#include "TransitionOStream.h"

#include "FSMFileStatistics.h"


//! \brief		Transition spécifique concernant l'entrée 
//!				dans un nouveau commentaire.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond à l'implémentation de la transition du même 
//!				nom sur le schéma de conception présenté 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
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
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class TransitionNewComment : public TransitionOStream
{
public:
	TransitionNewComment() = delete;
	//! Constructeur requérant le nom, la condition, l'état suivant, la 
	//! source des numéros de ligne, le nombre de 0 pour le formattage 
	//! du numéro de ligne et le flux de sortie. 
	TransitionNewComment(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, FSMFileStatistics const & fileStatistics, int linePaddingLength, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionNewComment() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;

private:
	FSMFileStatistics const & mFileStatistics;
	int mLinePaddingLength;
};

#endif // TRANSITION_NEW_COMMENT_H