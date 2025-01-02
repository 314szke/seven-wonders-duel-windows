#pragma once

#include "card.h"
#include "../io/card_loader.h"
#include "../management/order_manager.h"


class Deck {
public:
	Deck(const OrderManager& order_manager);

	void prepareTheFirstAge();
	void prepareTheSecondAge();
	void prepareTheThirdAge();

	void takeCard(const uint32_t visible_card_idx);
private:
	const OrderManager& manager;
	CardLoader card_loader;

	std::vector<Card*> visible_cards;
	std::vector<Card> deck;
};
