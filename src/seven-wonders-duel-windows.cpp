#include <iostream>
#include <vector>

#include "enums/exception_types.h"
#include "finance/bank.h"
#include "finance/market.h"
#include "game/game_table.h"


int main()
{
	try {
		Bank bank;
		Market market;
		std::vector<uint32_t> visible_coin_IDs = { 1,2,3,4,5 };
		GameTable table(visible_coin_IDs);
	}
	catch (ExceptionType exception) {
		std::cout << "ERROR: Caught exception with number " << (int) exception << std::endl;
	}
}
