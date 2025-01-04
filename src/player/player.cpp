#include "player.h"

#include "../enums/card_colors.h"


Player::Player(const PlayerID player_id, const std::string player_name) :
	ID(player_id),
	name(player_name),
	victory_points(0),
	number_of_cards_per_color(NUMBER_OF_CARD_COLORS, 0)
{}
