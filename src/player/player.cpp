#include "player.h"

#include "../enums/card_colors.h"


Player::Player(const PlayerID player_id, const std::string player_name) :
	ID(player_id),
	name(player_name),
	victory_points(0),
	blue_points(0),
	card_counter(NUMBER_OF_CARD_COLORS, 0)
{}

bool Player::hasChainSymbol(const ChainSymbol symbol) const
{
	for (uint32_t idx = 0; idx < chain_symbols.size(); idx++) {
		if (symbol == chain_symbols[idx]) {
			return true;
		}
	}
	return false;
}

bool Player::hasScienceSymbol(const ScienceSymbol symbol) const
{
	for (uint32_t idx = 0; idx < science_symbols.size(); idx++) {
		if (symbol == science_symbols[idx]) {
			return true;
		}
	}
	return false;
}

void Player::addChainSymbol(const ChainSymbol symbol)
{
	if (symbol != NO_CHAIN) {
		chain_symbols.push_back(symbol);
	}
}

void Player::addScienceSymbol(const ScienceSymbol symbol)
{
	if (symbol != NO_SCIENCE) {
		science_symbols.push_back(symbol);
	}
}
