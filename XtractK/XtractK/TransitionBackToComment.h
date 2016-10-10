//! \file TransitionBackToComment.h
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

#ifndef TRANSITION_BACK_TO_COMMENT_H
#define TRANSITION_BACK_TO_COMMENT_H


#include "TransitionOStream.h"


//! \brief		Transition spécifique concernant le retour à 
//!				l'état commentaire.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond à l'implémentation de la transition du même 
//!				nom sur le schéma de conception présenté 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
//!				
//!				Consiste en une surcharge de la fonction de traitement afin 
//!				d'afficher :
//!				 - symbole précédent
//!				 - symbole courant
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class TransitionBackToComment : public TransitionOStream
{
public:
	TransitionBackToComment() = delete;
	//! Constructeur requérant le nom, la condition, l'état 
	//! suivant et le flux de sortie. 
	TransitionBackToComment(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionBackToComment() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;
};

#endif // TRANSITION_IN_COMMENT_H