
//#define CHECK_MEMORY_LEAK
#ifdef CHECK_MEMORY_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#include "XtractC.h"


enum class ExitCode {	Ok = 0,  
						XtractCParamException = 1,
						XtractCException = 2,
						StdException = 3,
						NotHandled = 4
					};

int main(int argc, char **argv)
{

	try {
		XtractC xTractC;

		xTractC.setup(argc, argv);
		xTractC.process(true);
	}
	catch (XtractC::ParamException const & exception) {
		cout << "XtractC exception caught : " << endl << exception.what() << endl;
		cout << XtractC::CommandLineArgumentUsage << endl;
		system("pause");
		return static_cast<int>(ExitCode::XtractCParamException);
	}
	catch (XtractC::Exception const & exception) {
		cout << "XtractC exception caught : " << endl << exception.what() << endl;
		system("pause");
		return static_cast<int>(ExitCode::XtractCException);
	}
	catch (exception const & e) {
		cout << "std exception caught : "  << endl << e.what() << endl;
		system("pause");
		return static_cast<int>(ExitCode::StdException);
	}
	catch (...) {
		cout << "Unhandled exception!!!" << endl;
		system("pause");
		return static_cast<int>(ExitCode::NotHandled);
	}

	system("pause");

#ifdef CHECK_MEMORY_LEAK
	_CrtDumpMemoryLeaks();
#endif
	return static_cast<int>(ExitCode::Ok);
}




