#pragma once

#include "../deck/deck.h"
#include "../finance/bank.h"
#include "../finance/market.h"
#include "../management/order_manager.h"
#include "../game/game_table.h"


class Game {
public: 
	Game(const OrderManager& order_manager);

	Bank bank;
	Market market;
	Deck deck;
	GameTable table;
};
