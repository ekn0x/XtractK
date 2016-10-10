
//#define CHECK_MEMORY_LEAK
#ifdef CHECK_MEMORY_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#include "XtractK.h"


enum class ExitCode {	Ok = 0,  
						XtractKParamException = 1,
						XtractKException = 2,
						StdException = 3,
						NotHandled = 4
					};

int main(int argc, char **argv)
{

	try {
		XtractK xTractC;

		xTractC.setup(argc, argv);
		xTractC.process(true);
	}
	catch (XtractK::ParamException const & exception) {
		cout << "XtractK exception caught : " << endl << exception.what() << endl;
		cout << XtractK::CommandLineArgumentUsage << endl;
		system("pause");
		return static_cast<int>(ExitCode::XtractKParamException);
	}
	catch (XtractK::Exception const & exception) {
		cout << "XtractK exception caught : " << endl << exception.what() << endl;
		system("pause");
		return static_cast<int>(ExitCode::XtractKException);
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




