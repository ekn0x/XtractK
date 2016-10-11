//! \file TransitionKChar.h
//!
//! \brief Définition de la classe TransitionInComment.
//! \details Ce fichier fait partie du laboratoire 1 donné dans le cadre du cours 
//! <a href="https://cours.etsmtl.ca/gpa789/" target="_blank">GPA789 Analyse et conception orientées objet</a>.
//!
//! \version 1.0
//!

#ifndef TRANSITION_K_CHAR_H
#define TRANSITION_K_CHAR_H


#include "TransitionOStream.h"


//! \brief		Transition spécifique concernant un caractère 
//!				dans un commentaire.
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
//! \version	1.0
//! 
class TransitionKChar : public TransitionOStream
{
public:
	TransitionKChar() = delete;
	//! Constructeur requérant le nom, la condition, l'état 
	//! suivant et le flux de sortie. 
	TransitionKChar(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionKChar() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;
};

#endif // TRANSITION_K_CHAR_H