#include "consol_player.h"

#include <iostream>

#include "../enums/card_states.h"
#include "../io/consol_input.h"


ConsolPlayer::ConsolPlayer(const PlayerID player_id, const std::string player_name) :
	Player(player_id, player_name)
{}

uint32_t ConsolPlayer::play(const std::vector<Card*>& visible_cards)
{
	while (true) {
		std::cout << std::endl << name;
		int card_id = ConsolInput::ReadCardID();

		for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
			if ((visible_cards[idx]->state == CARD_VISIBLE) && (visible_cards[idx]->info.ID == card_id)) {
				return idx;
			}
		}

		std::cout << "WARNING: invalid card id << " << card_id << " >> !" << std::endl << std::endl;
	}
}
