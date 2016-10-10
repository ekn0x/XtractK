//! \file FSMFileStatistics.h
//!
//! \brief Définition de la classe FSMFileStatistics.
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

#ifndef FSM_LINE_COUNTER_H
#define FSM_LINE_COUNTER_H


#include "FiniteStateMachine.h"
#include <cstdint>

class State;
class TransitionCounter;


//! \brief		Automate dédié à l'extraction de statistiques simples 
//!				concernant un fichier texte.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond à l'implémentation de l'automate 
//!				de gauche présenté sur le schéma de conception présenté 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
//!				
//!				L'automate est complètement contenu et autonome.
//!
//!				Plusieurs fonctions permettent de retourner quelques données 
//!				statistiques :
//!				 - est-ce que le fichier est vide
//!				 - combien de lignes
//!				 - combien d'espaces (espace et tabulation)
//!				 - combien d'autres caractères (excluant les sauts de 
//!				 - ligne, espace et tabulation)
//!
//!				Ces fonctions tiennent compte de l'état courant de l'automate 
//!				et des caractères qui ont été traités jusqu'à ce moment.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class FSMFileStatistics final : public FiniteStateMachine
{
public:
	//! Contructeur par défaut.
	FSMFileStatistics();
	FSMFileStatistics(FSMFileStatistics const &) = delete;
	FSMFileStatistics(FSMFileStatistics const &&) = delete;
	FSMFileStatistics& operator=(FSMFileStatistics const &) = delete;
	FSMFileStatistics& operator=(FSMFileStatistics const &&) = delete;
	//! Destructeur par défaut.
	~FSMFileStatistics() = default;

	//! Retourne si le fichier est vide.
	bool isFileEmpty() const;
	//! Retourne le nombre de lignes (saut de ligne `\n`).
	uint32_t lineCount() const;
	//! Retourne le nombre d'espaces (espace et tabulation `\t`).
	uint32_t spaceCount() const;
	//! Retourne le nombre d'autres caractères (excluant l'espace, la tabulation `\t` et le saut de ligne `\t`).
	uint32_t characterCount() const;

private:
	State * mEmptyFile;
	State * mInLine;
	TransitionCounter * mStartByLine;
	TransitionCounter * mStartBySpace;
	TransitionCounter * mStartByCharacter;
	TransitionCounter * mLineCounter;
	TransitionCounter * mSpaceCounter;
	TransitionCounter * mCharacterCounter;
};


#endif // FSM_LINE_COUNTER_H
