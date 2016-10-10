//! \file FSMCppConstantExtraction.h
//!
//! \brief D�finition de la classe FSMCppConstantExtraction.
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

#ifndef FSM_CPP_CONSTANT_EXTRACTION_H
#define FSM_CPP_CONSTANT_EXTRACTION_H


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


//! \brief		Automate d�di� � l'extraction des commentaires d'
//!				un fichier du langage C/C++.
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond � l'impl�mentation de l'automate 
//!				de droite pr�sent� sur le sch�ma de conception pr�sent� 
//!				<a href="DiagrammeDEtats_ExtractionCommentairesCpp.png" target="_blank">ici</a>.
//!				
//!				L'automate est compl�tement contenu et autonome.
//!
//!				Plusieurs fonctions permettent de retourner quelques donn�es 
//!				statistiques :
//!				 - le nombre de commentaire style-C
//!				 - le nombre de commentaire style-C++
//!				 - le nombre de cha�nes de caract�res (`"abc"`)
//!				 - le nombre de caract�res (`'a'`)
//!
//!				Ces fonctions tiennent compte de l'�tat courant de l'automate 
//!				et des caract�res qui ont �t� trait�s jusqu'� ce moment.
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \version	1.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class FSMCppConstantExtraction final : public FiniteStateMachine
{
public:
	//! Constructeur par d�faut.
	FSMCppConstantExtraction() = delete;
	FSMCppConstantExtraction(FSMFileStatistics const & mFileStatistics, int linePaddingLength);
	FSMCppConstantExtraction(FSMCppConstantExtraction const &) = delete;
	FSMCppConstantExtraction(FSMCppConstantExtraction const &&) = delete;
	FSMCppConstantExtraction& operator=(FSMCppConstantExtraction const &) = delete;
	FSMCppConstantExtraction& operator=(FSMCppConstantExtraction const &&) = delete;
	//! Destructeur par d�faut.
	~FSMCppConstantExtraction() = default;

	//! Retourne le nombre de commentaire style-C : 
	//! `/* commentaire */`
	uint32_t cStyleCommentCount() const;
	//! Retourne le nombre de commentaire style-C++ : 
	//! `// commentaire`
	uint32_t cppStyleCommentCount() const;
	//! Retourne le nombre de cha�nes de caract�res tel 
	//! que d�fini en C/C++ : `"abc"`
	uint32_t stringCount() const;
	//! Retourne le nombre de caract�res tel que 
	//! d�fini en C/C++ : `'a'`
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


#endif // FSM_CPP_CONSTANT_EXTRACTION_H
