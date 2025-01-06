#include "game.h"


Game::Game(const OrderManager& order_manager) :
	age(FIRST_AGE),
	deck(order_manager),
	table(order_manager)
{}
