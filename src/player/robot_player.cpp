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
	std::vector<std::shared_ptr<const Card>> visible_cards = game.deck.getVisibleCards();
	std::shuffle(visible_cards.begin(), visible_cards.end(), engine);

	PlayerAction player_action;
	player_action.action_type = TAKE;

	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_VISIBLE && game.canPayFor(*this, visible_cards[idx])) {
			player_action.card = visible_cards[idx];
			player_action.card_id = player_action.card->info.ID;
			std::cout << name << " >> t " << player_action.card_id << std::endl;
			return player_action;
		}
	}

	player_action.action_type = DISCARD;
	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_VISIBLE) {
			player_action.card = visible_cards[idx];
			player_action.card_id = player_action.card->info.ID;
			std::cout << name << " >> d " << player_action.card_id << std::endl;
			return player_action;
		}
	}

	throw DECK_NO_VISIBLE_CARDS;
}

uint32_t RobotPlayer::selectWonder(const std::vector<std::shared_ptr<const Wonder>>& wonders)
{
	for (uint32_t idx = 0; idx < wonders.size(); idx++) {
		if (wonders[idx]->player_id == NO_PLAYER) {
			std::cout << name << " >> " << wonders[idx]->ID << std::endl;
			return wonders[idx]->ID;
		}
	}

	throw NO_WONDERS_TO_SELECT;
}

std::shared_ptr<const Card> RobotPlayer::chooseCard(const std::vector<std::shared_ptr<const Card>>& cards)
{
	std::cout << name << " >> " << cards[0]->info.ID << std::endl;
	return cards[0];
}

std::shared_ptr<const Card> RobotPlayer::chooseCardToDiscard(const std::vector<std::shared_ptr<const Card>>& cards)
{
	std::cout << name << " >> " << cards[0]->info.ID << std::endl;
	return cards[0];
}

