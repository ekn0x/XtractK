//! \file Symbol.h
//!
//! \brief Définition du type symbol_t
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

#ifndef SYMBOL_H
#define SYMBOL_H


//! \typedef symbol_t
//! \brief Type définissant les symboles utilisés par l'automate à états finis.
//! \details Conceptuellement, un AEF peut traiter une famille de symboles 
//!	représentant un dictionnaire des données pouvant être traitées. Dans le cas
//! d'un AEF faisant l'analyse lexicale d'un texte, l'ensemble des caractères
//! correspond aux symboles à manipuler.
//! 
//! Ce type fait partie des outils pour la création d'automates génériques.
//!				
typedef char symbol_t;


#endif // SYMBOL_H