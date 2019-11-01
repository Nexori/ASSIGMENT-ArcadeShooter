////----WARNING----//
////STICK TO x86 mode!!!
#include "Classes/Engine.h"
int main()
{
	try {
		Engine engine;
		engine.run();
	}
	catch (std::exception& e) {
		std::cout << "\nCRITICAL EXCEPTION: " << e.what() << endl;
	}
	//return 0;
}