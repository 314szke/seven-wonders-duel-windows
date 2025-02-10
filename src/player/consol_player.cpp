#include "consol_player.h"

#include <iostream>

#include "../enums/card_states.h"
#include "../game/game.h"
#include "../io/consol_input.h"
#include "../player/player_action.h"


ConsolPlayer::ConsolPlayer(const PlayerID player_id, const std::string player_name) :
	Player(player_id, player_name)
{}

PlayerAction ConsolPlayer::play(const Game& game)
{
	const std::vector<std::shared_ptr<Card>>& visible_cards = game.deck.getVisibleCards();

	while (true) {
		std::cout << std::endl << name << " ";
		PlayerAction player_action = ConsolInput::ReadPlayerAction();

		bool id_found = false;
		for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
			if ((visible_cards[idx]->state == CARD_VISIBLE) && (visible_cards[idx]->info.ID == player_action.card_id)) {
				id_found = true;

				player_action.card = visible_cards[idx];
				if (player_action.action_type == DISCARD) {
					return player_action;
				}
				
				if (game.canPayFor(*this, player_action.card)) {
					return player_action;
				} else { 
					std::cout << "WARNING: you can NOT pay for card " << player_action.card_id << "!" << std::endl;
					break;
				}
			}
		}

		if (!id_found) {
			if (player_action.action_type == INFO) {
				try {
					player_action.card = game.deck.getCard(player_action.card_id);
					return player_action;
				} catch (...) {
					std::cout << "WARNING: invalid card id " << player_action.card_id << " !" << std::endl << std::endl;
				}
			} else {
				std::cout << "WARNING: invalid card id " << player_action.card_id << " !" << std::endl << std::endl;
			}
		}
	}
}
