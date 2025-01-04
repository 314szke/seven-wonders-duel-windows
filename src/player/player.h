#pragma once

#include <string>
#include <vector>

#include "../enums/chain_symbols.h"
#include "../enums/player_id.h"
#include "../enums/science_symbols.h"
#include "../deck/card.h"
#include "../finance/material_bundle.h"


class Player {
protected: 
	Player(const PlayerID player_id, const std::string player_name);

public:
	PlayerID ID;
	virtual uint32_t play(const std::vector<Card*>& visible_cards) = 0;

protected:
	std::string name;
	uint32_t victory_points;

	// These can be removed by wonders
	std::vector<MaterialBundle> brown_cards;
	std::vector<MaterialBundle> grey_cards;

	std::vector<uint32_t> number_of_cards_per_color;
	std::vector<ChainSymbol> chain_symbols;
	std::vector<ScienceSymbol> science_symbols;
};
