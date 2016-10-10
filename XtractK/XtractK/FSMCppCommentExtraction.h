//! \file FSMCppCommentExtraction.h
//!
//! \brief Définition de la classe FSMCppCommentExtraction.
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

#ifndef FSM_CPP_COMMENT_EXTRACTION_H
#define FSM_CPP_COMMENT_EXTRACTION_H


#include "FiniteStateMachine.h"

#include <cstdint>
#include <ostream>
using namespace std;

class FSMFileStatistics;

class State;
class Transition;
class TransitionCounter;
class TransitionNewComment;
class TransitionInComment;
class TransitionBackToComment;
class TransitionExitingCStyle;
class TransitionExitingCppStyle;


//! \brief		Automate dédié à l'extraction des commentaires d'
//!				un fichier du langage C/C++.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond à l'implémentation de l'automate 
//!				de droite présenté sur le schéma de conception présenté 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
//!				
//!				L'automate est complètement contenu et autonome.
//!
//!				Plusieurs fonctions permettent de retourner quelques données 
//!				statistiques :
//!				 - le nombre de commentaire style-C
//!				 - le nombre de commentaire style-C++
//!				 - le nombre de chaînes de caractères (`"abc"`)
//!				 - le nombre de caractères (`'a'`)
//!
//!				Ces fonctions tiennent compte de l'état courant de l'automate 
//!				et des caractères qui ont été traités jusqu'à ce moment.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class FSMCppCommentExtraction final : public FiniteStateMachine
{
public:
	//! Constructeur par défaut.
	FSMCppCommentExtraction() = delete;
	FSMCppCommentExtraction(FSMFileStatistics const & mFileStatistics, int linePaddingLength);
	FSMCppCommentExtraction(FSMCppCommentExtraction const &) = delete;
	FSMCppCommentExtraction(FSMCppCommentExtraction const &&) = delete;
	FSMCppCommentExtraction& operator=(FSMCppCommentExtraction const &) = delete;
	FSMCppCommentExtraction& operator=(FSMCppCommentExtraction const &&) = delete;
	//! Destructeur par défaut.
	~FSMCppCommentExtraction() = default;

	//! Retourne le nombre de commentaire style-C : 
	//! `/* commentaire */`
	uint32_t cStyleCommentCount() const;
	//! Retourne le nombre de commentaire style-C++ : 
	//! `// commentaire`
	uint32_t cppStyleCommentCount() const;
	//! Retourne le nombre de chaînes de caractères tel 
	//! que défini en C/C++ : `"abc"`
	uint32_t stringCount() const;
	//! Retourne le nombre de caractères tel que 
	//! défini en C/C++ : `'a'`
	uint32_t characterCount() const;

private:
	State * sCode;
	State * sSlash;
	State * sCommentCStyle;
	State * sCommentCStyleStar;
	State * sCommentCppStyle;
	State * sCommentCppStyleEscapeChar;
	State * sString;
	State * sStringEscapeChar;
	State * sCharacter;
	State * sCharacterEscapeChar;

	Transition * tEnterSlash;
	Transition * tCancelSlash;

	TransitionNewComment * tEnterCommentCStyle;
	TransitionInComment * tCharCommentCStyle;
	Transition * tEnterStar;
	TransitionBackToComment * tCancelStar;
	TransitionInComment * tCommentStar;
	TransitionExitingCStyle * tExitCommentCStyle;

	TransitionNewComment * tEnterCommentCppStyle;
	TransitionInComment * tCharCommentCppStyle;
	TransitionExitingCppStyle * tExitCommentCppStyle;
	Transition * tEnterEscapeCharComCppStyle;
	TransitionBackToComment * tExitEscapeCharComCppStyle;

	TransitionCounter * tEnterString;
	Transition * tExitString;
	Transition * tEnterEscapeCharString;
	Transition * tExitEscapeCharString;

	TransitionCounter * tEnterCharacter;
	Transition * tExitCharacter;
	Transition * tEnterEscapeCharCharacter;
	Transition * tExitEscapeCharCharacter;

};


#endif // FSM_CPP_COMMENT_EXTRACTION_H
