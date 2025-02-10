#include "robot_player.h"

#include <iostream>

#include "../enums/exception_types.h"
#include "../game/game.h"


RobotPlayer::RobotPlayer(const PlayerID player_id, const std::string player_name) :
	Player(player_id, player_name),
	engine(rd())
{}

PlayerAction RobotPlayer::play(const Game& game)
{
	std::vector<std::shared_ptr<Card>> visible_cards = game.deck.getVisibleCards();
	std::shuffle(visible_cards.begin(), visible_cards.end(), engine);

	PlayerAction player_action;
	player_action.action_type = TAKE;

	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_VISIBLE && game.canPayFor(*this, visible_cards[idx])) {
			player_action.card = visible_cards[idx];
			player_action.card_id = player_action.card->info.ID;
			std::cout << std::endl << name << " >> t " << player_action.card_id << std::endl;
			return player_action;
		}
	}

	player_action.action_type = DISCARD;
	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_VISIBLE) {
			player_action.card = visible_cards[idx];
			player_action.card_id = player_action.card->info.ID;
			std::cout << std::endl << name << " >> d " << player_action.card_id << std::endl;
			return player_action;
		}
	}

	throw DECK_NO_VISIBLE_CARDS;
}

