#include "XtractC.h"

#include <sstream>



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractC
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const string XtractC::OpenInputFileErrorString{ "Le nom du fichier d'entree est invalide ou il existe une restriction d'access sur ce fichier." };
const string XtractC::OpenOutputFileErrorString{ "Le nom du fichier de sortie est invalide ou il existe une restriction d'access sur ce fichier." };
const string XtractC::ReadCharacterFromInputFileString{ "Impossible de lire un caractère." };
const string XtractC::CommandLineArgumentUsage{ R"(
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Programme XtractC - Extraction de commentaires d'un fichier source du langage C++
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Usage : xtractc infile [outfile]
  - infile : est le fichier source C/C++ (*.h, *.hpp, *.c, *.cpp)
  - outfile : est le fichier de sortie
              si non specifie, la sortie est redirigee vers la sortie standard
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
)" };

XtractC::XtractC()
	:	mOStream{ &cout },
		mFSMCppComExt(mFSMFileStatistics, 4)
{
}

void XtractC::setup(const string & inputFileName)
{
	openInputFile(inputFileName);

	mOStream = &cout;

	mFSMCppComExt.setStream(mOStream);
}

void XtractC::setup(const string & inputFileName, const string & outputFileName)
{
	openInputFile(inputFileName);
	openOutputFile(outputFileName);

	mOStream = &mOutputFile;

	mFSMCppComExt.setStream(mOStream);
}

void XtractC::setup(const string & inputFileName, stringstream & outputstring)
{
	openInputFile(inputFileName);

	mOStream = &outputstring;

	mFSMCppComExt.setStream(mOStream);
}

void XtractC::setup(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		throw ParamException(__FUNCSIG__);
	}

	switch (argc) {
		case 2 :
			setup(argv[1]);
			break;
		case 3 :
			setup(argv[1], argv[2]);
			break;
	}
}

void XtractC::openInputFile(const string & inputFileName)
{
	mInputFile.open(inputFileName, ios::in);

	if (mInputFile.fail()) {
		throw Exception(__FUNCSIG__, OpenInputFileErrorString);
	}
}

void XtractC::openOutputFile(const string & outputFileName)
{
	mOutputFile.open(outputFileName, ios::out | ios::trunc);

	if (mOutputFile.fail()) {
		throw Exception(__FUNCSIG__, OpenOutputFileErrorString);
	}
}

void XtractC::process(bool includeStats)
{
	mFSMFileStatistics.start();
	mFSMCppComExt.start();

	symbol_t symbol;
	while (!mInputFile.eof()) {
		mInputFile.get(symbol);
		if (!mInputFile.eof()) {
			if (mInputFile.fail()) {
				throw Exception(__FUNCSIG__, ReadCharacterFromInputFileString);
			}
			mFSMFileStatistics.processSymbol(symbol);
			mFSMCppComExt.processSymbol(symbol);
		}
	}

	mFSMStatisticsSuccess = mFSMFileStatistics.stop();
	mFSMCommentsSuccess = mFSMCppComExt.stop();

	if (includeStats) {
		writeStats();
	}
}

void XtractC::writeStats()
{
	*mOStream << endl << endl;
	*mOStream << "File statistics :" << endl;
	*mOStream << "Number of lines : " << mFSMFileStatistics.lineCount() << endl;
	*mOStream << "Number of spaces : " << mFSMFileStatistics.spaceCount() << endl;
	*mOStream << "Number of other characters : " << mFSMFileStatistics.characterCount() << endl;
	*mOStream << "Number of C-style comments : " << mFSMCppComExt.cStyleCommentCount() << endl;
	*mOStream << "Number of C++-style comments : " << mFSMCppComExt.cppStyleCommentCount() << endl;
	*mOStream << "Number of strings : " << mFSMCppComExt.stringCount() << endl;
	*mOStream << "Number of character : " << mFSMCppComExt.characterCount() << endl;
	*mOStream << endl << "Accepting state :" << endl;
	*mOStream << "Statistics FSM returned with success : " << std::boolalpha << mFSMStatisticsSuccess << endl;
	*mOStream << "Comments FSM returned with success : " << std::boolalpha << mFSMCommentsSuccess << endl;
	*mOStream << endl;
}





// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractC::Exception
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
XtractC::Exception::Exception(const string & context, const string & cause)
	:	mContext{ context },
		mCause{ cause }
{
}

string XtractC::Exception::what() const
{
	stringstream strStream;

	strStream	<< "Exception levee : XtractC::Exception" << endl
				<< "  - Contexte : " << mContext << endl
				<< "  - Cause possible : " << mCause << endl;

	return strStream.str();
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// XtractC::ParamException
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const string XtractC::ParamException::CauseString{ "Parametre(s) d'entree invalide(s)." };

XtractC::ParamException::ParamException()
	:	Exception("", CauseString)
{
}

XtractC::ParamException::ParamException(const string & context)
	: Exception(context, CauseString)
{
}

