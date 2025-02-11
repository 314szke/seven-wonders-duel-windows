#include "consol_player.h"

#include <iostream>

#include "../constants.h"
#include "../enums/card_states.h"
#include "../display/card_displayer.h"
#include "../display/deck_displayer.h"
#include "../display/help_displayer.h"
#include "../game/game.h"
#include "../io/consol_input.h"
#include "../player/player_action.h"


ConsolPlayer::ConsolPlayer(const PlayerID player_id, const std::string player_name) :
	Player(player_id, player_name)
{}

PlayerAction ConsolPlayer::play(const Game& game)
{
	while (true) {
		PlayerAction action = ConsolInput::ReadPlayerAction(name);
		
		if (action.action_type == HELP) {
			HelpDisplayer::Show();
			continue;
		} else if (action.action_type == SHOW_TABLE) {
			return action;
		} else if (action.action_type == INFO_ALL) {
			CardDisplayer::Show(game.deck.getVisibleCards());
			continue;
		}
		
		try {
			if (action.action_type == TAKE) {
				action.card = game.deck.getVisibleCard(action.card_id);
			} else {
				action.card = game.deck.getCard(action.card_id);
			}
		}
		catch (...) {
			if ((action.card_id < 0) || (action.card_id >= TOTAL_NUMBER_OF_CARDS)) {
				std::cout << "WARNING: invalid card id " << action.card_id << " !" << std::endl << std::endl;
			} else {
				std::cout << "WARNING: card with id " << action.card_id << " is not visible!" << std::endl << std::endl;
			}
			continue;
		}

		
		if (action.action_type == INFO) {
			CardDisplayer::Show(action.card);
			continue;
		} else if ((action.action_type == TAKE) && (!game.canPayFor(*this, action.card))) {
			std::cout << "WARNING: you can NOT pay for card " << action.card_id << "!" << std::endl;
			continue;
		}

		return action;
	}
}
