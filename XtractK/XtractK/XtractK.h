//! \file XtractK.h
//!
//! \brief Définition de la classe XtractK.
//! \details Cette classe est la base du mécanisme d'extraction des constantes d'un fichier
//!
//! \version 1.0
//!
//! \author Alexandre Hallée-Lamarche
//!
//! \date 2000-2016
//! \copyright Copyleft 2000-2016

#ifndef X_TRACT_K_H
#define X_TRACT_K_H


#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "FSMFileStatistics.h"
#include "FSMCppConstantExtraction.h"

//! \brief		Classe gérant les paramètres du projet. 
//! \details	Cette classe fait partie de la solution XtractC. 
//! 
//!				Elle correspond à l'encapsulation de tous les éléments 
//!				nécessaire au programme requis :
//!				 - gestion des arguments passés en ligne de commande
//!				 - gestion des deux automates
//!				 - lecture du fichier source caractère par caractère 
//!					et assignation aux automates
//!				 - gestion des exception des entrées / sorties
//!				 - affichage des statistiques finales
//!
//!				De plus, XtractC possède deux classes internes utilisées 
//!				pour la gestion d'exception (Exception et ParamException).
//! \author		Tony Wong, Ph.D.
//! \author		JC Demers
//! \author		Alexandre Hallée-Lamarche
//! \version	2.0
//! \date		20/08/2016
//! \copyright	Copyleft 2000-2016
class XtractK
{
public:
	//! Constructeur.
	XtractK();
	//! Destructeur par défaut.
	~XtractK() = default;

	//! Texte expiquant le synopsis de la fonction.
	static const string CommandLineArgumentUsage;

	//! Initialisation de la classe. Le fichier d'entrée est spécifié 
	//! et la sortie est produite directement sur la console.
	void setup(const string & inputFileName);
	//! Initialisation de la classe. Le fichier d'entrée est spécifié 
	//! et la sortie est produite dans le fichier spécifié.
	void setup(const string & inputFileName, const string & outputFileName);
	//! Initialisation de la classe. Le fichier d'entrée est spécifié 
	//! et la sortie est produite dans le fichier spécifié.
	void setup(const string & inputFileName, stringstream & outputstring);
	//! Initialisation de la classe en analysant les arguments passés 
	//! par la ligne de commande.
	void setup(int argc, char **argv);

	//! Effectue tout le traitement des automates sur le fichier d'entrée
	//! déjà donné. Il est important d'avoir initialiser la classe avec 
	//! `setup`.
	void process(bool includeStats);

	class Exception;
	class ParamException;

private:
	static const string OpenInputFileErrorString;
	static const string OpenOutputFileErrorString;
	static const string ReadCharacterFromInputFileString;

	ifstream mInputFile;
	ofstream mOutputFile;
	ostream * mOStream;
	bool mFSMStatisticsSuccess;
	bool mFSMCommentsSuccess; // Peut etre que l'on va devoir changer ca

	void openInputFile(const string & inputFileName);
	void openOutputFile(const string & outputFileName);
	void writeStats();

	FSMFileStatistics mFSMFileStatistics;
	FSMCppConstantExtraction mFSMCppKExt;
};




//! \exception XtractC::Exception
//! \brief	Classe utilitaire de XtractC pour la gestion d'exception générale.
class XtractK::Exception
{
public:
	Exception() = default;
	Exception(const string & context, const string & cause);
	virtual ~Exception() = default;

	void setContext(const string& context) { mContext = context; }
	void setCause(const string& cause) { mCause = cause; }

	const string& context() const { return mContext; }
	const string& cause() const { return mCause; }

	string what() const;

protected:
	string mContext;
	string mCause;
};



//! \exception XtractC::ParamException
//! \brief	Classe utilitaire de XtractC pour la gestion d'exception reliée aux paramètres.
class XtractK::ParamException : public XtractK::Exception
{
public:
	ParamException();
	ParamException(const string & context);
	~ParamException() = default;

private:
	static const string CauseString;
	using Exception::setCause;
};


#endif // X_TRACT_K_H