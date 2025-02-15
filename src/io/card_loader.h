#pragma once

#include <memory>

#include "parser.h"
#include "../deck/card.h"


class CardLoader : private Parser {
public:
	CardLoader();
	
	std::shared_ptr<const Card> getCard(const uint32_t card_id) const;
	std::shared_ptr<Card> getCard(const uint32_t card_id);

private:
	void parseCard(const uint32_t card_id, const std::smatch& match);

	std::vector<std::shared_ptr<Card>> cards;
};

