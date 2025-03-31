#include <iostream>
#include <sstream>
#include <vector>

#include "game/game.h"
#include "management/game_manager.h"
#include "management/order_manager.h"


int main()
{
	OrderManager order_manger;
	Game game(order_manger);
	GameManager manager(game, order_manger);

	manager.initializeGame();

	while (manager.gameIsOn()) {
		manager.handleTurn();
	}
	manager.declareWinner();
}
