#include <iostream>

#include "bank.h"
#include "exception_types.h"


int main()
{
	try {
		Bank bank;
	}
	catch (ExceptionType exception) {
		std::cout << "ERROR: Caught exception with number " << (int) exception << std::endl;
	}
}
