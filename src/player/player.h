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
	std::string name;

	virtual uint32_t play(const std::vector<Card*>& visible_cards) = 0;

	bool hasChainSymbol(const ChainSymbol symbol) const;

	const std::vector<ChainSymbol>& getChainSymbols() const;
	const std::vector<ScienceSymbol>& getScienceSymbols() const;
	uint32_t getVictoryPoints() const;

protected:
	uint32_t victory_points;

	// These can be removed by wonders
	std::vector<MaterialBundle> brown_cards;
	std::vector<MaterialBundle> grey_cards;

	std::vector<ChainSymbol> chain_symbols;
	std::vector<ScienceSymbol> science_symbols;
};
