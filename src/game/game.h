#pragma once

#include "../deck/deck.h"
#include "../enums/card_age_types.h"
#include "../finance/bank.h"
#include "../finance/market.h"
#include "../management/order_manager.h"
#include "../game/game_table.h"
#include "../player/player.h"


class Game {
public: 
	Game(const OrderManager& order_manager);

	bool canPayFor(const Player& player, const Card* card) const;
	uint32_t getPriceFor(const Player& player, const Card* card) const;

	CardAgeType age;
	Bank bank;
	Market market;
	Deck deck;
	GameTable table;
};
