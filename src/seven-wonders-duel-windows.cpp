#include <iostream>

#include "enums/exception_types.h"
#include "finance/bank.h"
#include "finance/market.h"


int main()
{
	try {
		Bank bank;
		Market market;
	}
	catch (ExceptionType exception) {
		std::cout << "ERROR: Caught exception with number " << (int) exception << std::endl;
	}
}
