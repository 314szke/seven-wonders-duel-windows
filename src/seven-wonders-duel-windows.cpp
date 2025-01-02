#include <iostream>

#include "enums/exception_types.h"
#include "finance/bank.h"


int main()
{
	try {
		Bank bank;
	}
	catch (ExceptionType exception) {
		std::cout << "ERROR: Caught exception with number " << (int) exception << std::endl;
	}
}
