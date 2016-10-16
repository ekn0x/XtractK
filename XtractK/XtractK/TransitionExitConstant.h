//! \file TransitionExitingCppStyle.h
//!
//! \brief D�finition de la classe TransitionExitingCppStyle.
//! \details Ce fichier fait partie du laboratoire 1 donn� dans le cadre du cours 
//! <a href="https://cours.etsmtl.ca/gpa789/" target="_blank">GPA789 Analyse et conception orient�es objet</a>.
//!
//! \version 1.0
//!
//! \author Tony Wong, Ph.D.\n
//!		D�partement de g�nie de production automatis�e\n
//!		�cole de technologie sup�rieure\n
//!		tony.wong@etsmtl.ca
//! \author	JC Demers
//!
//! \date 2000-2016
//! \copyright Copyleft 2000-2016

#ifndef TRANSITION_EXIT_CONSTANT_H
#define TRANSITION_EXIT_CONSTANT_H


#include "TransitionOStream.h"


class TransitionExitConstant : public TransitionOStream
{
public:
	TransitionExitConstant() = delete;
	//! Constructeur requ�rant le nom, la condition, l'�tat 
	//! suivant et le flux de sortie. 
	TransitionExitConstant(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par d�faut.
	virtual ~TransitionExitConstant() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;
};

#endif // TRANSITION_EXIT_CONSTANT_H
