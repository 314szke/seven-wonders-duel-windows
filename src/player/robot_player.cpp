#include "robot_player.h"

#include "../enums/exception_types.h"


RobotPlayer::RobotPlayer(const PlayerID player_id, const std::string player_name) :
	Player(player_id, player_name)
{}

uint32_t RobotPlayer::play(const std::vector<Card*>& visible_cards)
{
	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_VISIBLE) {
			return idx;
		}
	}

	throw DECK_NO_VISIBLE_CARDS;
}

