#pragma once

#include "parser.h"
#include "../deck/card.h"


class CardLoader : private Parser {
public:
	CardLoader();
	
	Card* getCard(const uint32_t card_id);

private:
	void parseCardDetails(const uint32_t card_id, const std::smatch& match);

	std::vector<Card> cards;
};

