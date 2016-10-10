#include "XtractK.h"

#include <sstream>



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractK
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const string XtractK::OpenInputFileErrorString{ "Le nom du fichier d'entree est invalide ou il existe une restriction d'access sur ce fichier." };
const string XtractK::OpenOutputFileErrorString{ "Le nom du fichier de sortie est invalide ou il existe une restriction d'access sur ce fichier." };
const string XtractK::ReadCharacterFromInputFileString{ "Impossible de lire un caractère." };
const string XtractK::CommandLineArgumentUsage{ R"(
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Programme XtractK - Extraction de commentaires d'un fichier source du langage C++
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Usage : xtractc infile [outfile]
  - infile : est le fichier source C/C++ (*.h, *.hpp, *.c, *.cpp)
  - outfile : est le fichier de sortie
              si non specifie, la sortie est redirigee vers la sortie standard
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
)" };

XtractK::XtractK()
	: mOStream{ &cout },
	mFSMCppKExt(mFSMFileStatistics, 4)
{
}

void XtractK::setup(const string & inputFileName)
{
	openInputFile(inputFileName);

	mOStream = &cout;

	mFSMCppKExt.setStream(mOStream);
}

void XtractK::setup(const string & inputFileName, const string & outputFileName)
{
	openInputFile(inputFileName);
	openOutputFile(outputFileName);

	mOStream = &mOutputFile;

	mFSMCppKExt.setStream(mOStream);
}

void XtractK::setup(const string & inputFileName, stringstream & outputstring)
{
	openInputFile(inputFileName);

	mOStream = &outputstring;

	mFSMCppKExt.setStream(mOStream);
}

void XtractK::setup(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		throw ParamException(__FUNCSIG__);
	}

	switch (argc) {
	case 2:
		setup(argv[1]);
		break;
	case 3:
		setup(argv[1], argv[2]);
		break;
	}
}

void XtractK::openInputFile(const string & inputFileName)
{
	mInputFile.open(inputFileName, ios::in);

	if (mInputFile.fail()) {
		throw Exception(__FUNCSIG__, OpenInputFileErrorString);
	}
}

void XtractK::openOutputFile(const string & outputFileName)
{
	mOutputFile.open(outputFileName, ios::out | ios::trunc);

	if (mOutputFile.fail()) {
		throw Exception(__FUNCSIG__, OpenOutputFileErrorString);
	}
}

void XtractK::process(bool includeStats)
{
	mFSMFileStatistics.start();
	mFSMCppKExt.start();

	symbol_t symbol;
	while (!mInputFile.eof()) {
		mInputFile.get(symbol);
		if (!mInputFile.eof()) {
			if (mInputFile.fail()) {
				throw Exception(__FUNCSIG__, ReadCharacterFromInputFileString);
			}
			mFSMFileStatistics.processSymbol(symbol);
			mFSMCppKExt.processSymbol(symbol);
		}
	}

	mFSMStatisticsSuccess = mFSMFileStatistics.stop();
	mFSMCommentsSuccess = mFSMCppKExt.stop();

	if (includeStats) {
		writeStats();
	}
}

void XtractK::writeStats()
{
	*mOStream << endl << endl;
	*mOStream << "File statistics :" << endl;
	*mOStream << "Number of lines : " << mFSMFileStatistics.lineCount() << endl;
	*mOStream << "Number of spaces : " << mFSMFileStatistics.spaceCount() << endl;
	*mOStream << "Number of other characters : " << mFSMFileStatistics.characterCount() << endl;
	*mOStream << "Number of C-style comments : " << mFSMCppKExt.cStyleCommentCount() << endl;
	*mOStream << "Number of C++-style comments : " << mFSMCppKExt.cppStyleCommentCount() << endl;
	*mOStream << "Number of strings : " << mFSMCppKExt.stringCount() << endl;
	*mOStream << "Number of character : " << mFSMCppKExt.characterCount() << endl;
	*mOStream << endl << "Accepting state :" << endl;
	*mOStream << "Statistics FSM returned with success : " << std::boolalpha << mFSMStatisticsSuccess << endl;
	*mOStream << "Comments FSM returned with success : " << std::boolalpha << mFSMCommentsSuccess << endl;
	*mOStream << endl;
}





// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractK::Exception
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
XtractK::Exception::Exception(const string & context, const string & cause)
	: mContext{ context },
	mCause{ cause }
{
}

string XtractK::Exception::what() const
{
	stringstream strStream;

	strStream << "Exception levee : XtractK::Exception" << endl
		<< "  - Contexte : " << mContext << endl
		<< "  - Cause possible : " << mCause << endl;

	return strStream.str();
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractK::ParamException
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const string XtractK::ParamException::CauseString{ "Parametre(s) d'entree invalide(s)." };

XtractK::ParamException::ParamException()
	: Exception("", CauseString)
{
}

XtractK::ParamException::ParamException(const string & context)
	: Exception(context, CauseString)
{
}

