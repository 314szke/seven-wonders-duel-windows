#include "game.h"


Game::Game(const OrderManager& order_manager) :
	age(FIRST_AGE),
	deck(order_manager),
	table(order_manager),
	wonder_manager(order_manager)
{}

bool Game::canPayFor(const Player& player, std::shared_ptr<const Card> card) const
{
	uint32_t price = getPriceFor(player, card);
	return bank.creditCheck(player.ID, price);
}

bool Game::canPayFor(const Player& player, std::shared_ptr<const Wonder> wonder) const
{
	uint32_t price = market.getMaterialPrice(player.ID, wonder->material_cost);
	return bank.creditCheck(player.ID, price);
}

uint32_t Game::getPriceFor(const Player& player, std::shared_ptr<const Card> card) const
{
	if (player.hasChainSymbol(card->cost.symbol)) {
		return 0;
	}

	uint32_t price = card->cost.money;
	price += market.getMaterialPrice(player.ID, card->cost.materials);
	return  price;
}
