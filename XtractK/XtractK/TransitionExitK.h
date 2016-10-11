//! \file TransitionExitK.h
//!
//! \brief D�finition de la classe TransitionInComment.
//! \details Ce fichier fait partie du laboratoire 1 donn� dans le cadre du cours 
//! <a href="https://cours.etsmtl.ca/gpa789/" target="_blank">GPA789 Analyse et conception orient�es objet</a>.
//!
//! \version 1.0
//!

#ifndef TRANSITION_EXIT_K_H
#define TRANSITION_EXIT_K_H


#include "TransitionOStream.h"


//! \brief		Transition sp�cifique concernant un caract�re 
//!				dans un commentaire.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond � l'impl�mentation de la transition du m�me 
//!				nom sur le sch�ma de conception pr�sent� 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
//!				
//!				Consiste en une surcharge de la fonction de traitement afin 
//!				d'afficher :
//!				 - symbole pr�c�dent
//!				 - symbole courant
//! \version	1.0
//! 
class TransitionExitK : public TransitionOStream
{
public:
	TransitionExitK() = delete;
	//! Constructeur requ�rant le nom, la condition, l'�tat 
	//! suivant et le flux de sortie. 
	TransitionExitK(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par d�faut.
	virtual ~TransitionExitK() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;
};

#endif // TRANSITION_EXIT_K_H
