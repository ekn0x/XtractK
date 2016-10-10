//! \file TransitionOStream.h
//!
//! \brief Définition de la classe TransitionOStream.
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

#ifndef TRANSITION_O_STREAM_H
#define TRANSITION_O_STREAM_H


#include "TransitionCounter.h"

#include <iostream>
using namespace std;


//! \brief		Classe représentant des transitions qui doivent produire 
//!				une sortie vers l'écran ou un fichier.
//! \details	Cette classe fait partie des outils pour la création d'automates 
//!				génériques.
//! 
//!				Cette classe permet de créer une interface commune pour 
//!				l'accès au flux de sortie. 
//!				L'interface commune est la gestion de l'objet du flux 
//!				de sortie `ostream`.
//!
//!				Par défaut, le flux de sortie est dirigé vers l'écran. 
//!				Il est possible de préciser le flux désiré.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class TransitionOStream : public TransitionCounter
{
public:
	TransitionOStream() = delete;
	//! Constructeur. Il est nécessaire de donner un nom, l'état suivant, 
	//! la condition et le flux de sortie utilisé.
	TransitionOStream(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState, ostream * stream = &cout);
	//! Destructeur par défaut.
	virtual ~TransitionOStream() = default;

	//! Détermine le flux de sortie spécifié.
	void setStream(ostream * stream) { mStream = stream; }
	//! Retourne le flux de sortie utilisé.
	ostream* stream() { return mStream; }

protected:
	ostream * mStream;
};

#endif // TRANSITION_O_STREAM_H