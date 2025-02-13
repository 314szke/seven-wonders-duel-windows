#pragma once

#include <string>
#include <vector>

#include "../enums/chain_symbols.h"
#include "../enums/player_id.h"
#include "../enums/science_symbols.h"
#include "../finance/material_bundle.h"
#include "../player/player_action.h"


class Game;


class Player {
protected: 
	Player(const PlayerID player_id, const std::string player_name);

public:
	virtual PlayerAction play(const Game& game) = 0;
	
	uint32_t getNumberOfBuiltWonders() const;

	bool hasChainSymbol(const ChainSymbol symbol) const;
	bool hasScienceSymbol(const ScienceSymbol symbol) const;

	void addChainSymbol(const ChainSymbol symbol);
	void addScienceSymbol(const ScienceSymbol symbol);

	PlayerID ID;
	std::string name;
	uint32_t victory_points;
	uint32_t blue_points; // in case of victory point egality, blue card points count

	// These can be removed by wonders
	std::vector<uint32_t> card_counter;
	std::vector<std::shared_ptr<const Card>> brown_cards;
	std::vector<std::shared_ptr<const Card>> grey_cards;
	std::vector<std::shared_ptr<const Card>> guild_cards;

	std::vector<ChainSymbol> chain_symbols;
	std::vector<ScienceSymbol> science_symbols;
};
