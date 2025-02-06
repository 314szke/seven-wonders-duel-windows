#include "player.h"

#include "../enums/card_colors.h"


Player::Player(const PlayerID player_id, const std::string player_name) :
	ID(player_id),
	name(player_name),
	victory_points(0)
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
