#include "game.h"


Game::Game(const OrderManager& order_manager) :
	deck(order_manager),
	table(order_manager)
{}
