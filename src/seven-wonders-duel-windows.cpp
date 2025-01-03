#include <iostream>
#include <vector>

#include "enums/exception_types.h"
#include "management/game_manager.h"


int main()
{
	try {
		GameManager manager;
		manager.setTheThirdStage();
	}
	catch (ExceptionType exception) {
		std::cout << "ERROR: Caught exception with number " << (int) exception << std::endl;
	}
}
