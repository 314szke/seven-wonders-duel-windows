#include <iostream>
#include <sstream>
#include <vector>

#include "enums/exception_types.h"
#include "management/game_manager.h"


int main()
{
	GameManager manager;
	manager.setTheFirstStage();

	int card_id;
	std::string line;
	std::stringstream ss;
	while (manager.gameIsOn()) {
		manager.showTable();

		do {
			std::cout << "Pick a card! >> ";
			std::getline(std::cin, line);
			ss << line;
			ss >> card_id;
			ss.str(std::string());
			ss.clear();
			
			if (card_id == 0) {
				std::cout << "WARING: invalid input << " << line << " >> !" << std::endl;
			} else {
				std::cout << std::endl;
			}
		} while (card_id == 0);

		manager.takeCardFromConsol(card_id);
	}
}
