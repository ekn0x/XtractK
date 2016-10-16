//! \file TransitionExitingCppStyle.h
//!
//! \brief Définition de la classe TransitionExitingCppStyle.
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

#ifndef TRANSITION_EXIT_CONSTANT_H
#define TRANSITION_EXIT_CONSTANT_H


#include "TransitionOStream.h"


class TransitionExitConstant : public TransitionOStream
{
public:
	TransitionExitConstant() = delete;
	//! Constructeur requérant le nom, la condition, l'état 
	//! suivant et le flux de sortie. 
	TransitionExitConstant(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionExitConstant() = default;

	//! Surcharge permettant d'afficher les informations requises.
	virtual void process(symbol_t prevSymbol, symbol_t curSymbol) override;
};

#endif // TRANSITION_EXIT_CONSTANT_H
