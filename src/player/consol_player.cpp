#include "consol_player.h"

#include <iostream>

#include "../constants.h"
#include "../enums/card_states.h"
#include "../display/card_displayer.h"
#include "../display/deck_displayer.h"
#include "../display/help_displayer.h"
#include "../display/wonder_displayer.h"
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
		
		switch (action.action_type) {
			case HELP: HelpDisplayer::Show(); break;
			case INFO_ALL: CardDisplayer::Show(game.deck.getVisibleCards()); break;
			case SHOW_TABLE: return action;
			default: {
				if (processAction(game, action)) {
					return action;
				}
			}
		}
	}
}

uint32_t ConsolPlayer::selectWonder(const std::vector<std::shared_ptr<const Wonder>>& wonders)
{
	while (true) {
		uint32_t wonder_id = ConsolInput::ReadWonderChoice(name);
		
		bool found = false;
		for (uint32_t idx = 0; idx < wonders.size(); idx++) {
			if ((wonders[idx]->ID == wonder_id) && (wonders[idx]->player_id == NO_PLAYER)) {
				return wonder_id;
			} else if ((wonders[idx]->ID == wonder_id) && (wonders[idx]->player_id != NO_PLAYER)) {
				found = true;
				std::cout << "WARNING: wonder " << wonder_id << " is already taken!" << std::endl;
			}
		}
		if (!found) {
			std::cout << "WARNING: wonder " << wonder_id << " is invalid!" << std::endl;
		}
	}
}

std::shared_ptr<const Card> ConsolPlayer::chooseCard(const std::vector<std::shared_ptr<const Card>>& cards)
{
	return chooseCard(cards, "Choose a card from the discard pile!");
}

std::shared_ptr<const Card> ConsolPlayer::chooseCardToDiscard(const std::vector<std::shared_ptr<const Card>>& cards)
{
	return chooseCard(cards, "Choose a card to discard from the adversary!");
}

bool ConsolPlayer::processAction(const Game& game, PlayerAction& action)
{
	if (!getActionCard(game, action)) {
		return false;
	}
	
	if (!getActionWonder(game, action)) {
		return false;
	}
	
	if (action.action_type == INFO) {
		CardDisplayer::Show(action.card);
		return true;
	}

	if (action.action_type == WONDER) {
		WonderDisplayer::Show(action.wonder);
		return true;
	}
	
	if ((action.action_type == TAKE) && (!game.canPayFor(*this, action.card))) {
		std::cout << "WARNING: you can NOT pay for card " << action.card_id << "!" << std::endl;
		return false;
	}

	if ((action.action_type == BUILD) && (!game.canPayFor(*this, action.wonder))) {
		std::cout << "WARNING: you can NOT pay for wonder " << action.wonder_id << "!" << std::endl;
		return false;
	}

	return true;
}

bool ConsolPlayer::getActionCard(const Game& game, PlayerAction& action)
{
	try {
		if (action.isFinal()) {
			action.card = game.deck.getVisibleCard(action.card_id);
		} else if (action.action_type != WONDER){
			action.card = game.deck.getCard(action.card_id);
		}
		return true;
	}
	catch (...) {
		if ((action.card_id < 0) || (action.card_id >= TOTAL_NUMBER_OF_CARDS)) {
			std::cout << "WARNING: invalid card id " << action.card_id << " !" << std::endl;
		} else {
			std::cout << "WARNING: card with id " << action.card_id << " is not accessible!" << std::endl;
		}
	}
	return false;
}

bool ConsolPlayer::getActionWonder(const Game& game, PlayerAction& action)
{
	try {
		if ((action.action_type == BUILD) || (action.action_type == WONDER)) {
			action.wonder = game.wonder_manager.getWonder(action.wonder_id);
		}
	}
	catch (...) {
		std::cout << "WARNING: invalid wonder id " << action.wonder_id << " !" << std::endl;
		return false;
	}

	if (action.action_type == BUILD) {
		if (action.wonder->player_id != ID) {
			std::cout << "WARNING: wonder " << action.wonder_id << " does not belong to " << name << "!" << std::endl;
			return false;
		}
		else if (action.wonder->isBuilt()) {
			std::cout << "WARNING: wonder " << action.wonder_id << " is already built!" << std::endl;
			return false;
		}
	}

	return true;
}

std::shared_ptr<const Card> ConsolPlayer::chooseCard(const std::vector<std::shared_ptr<const Card>>& cards, std::string message)
{
	while (true) {
		CardDisplayer::Show(cards);
		std::cout << message << std::endl;
		uint32_t card_id = ConsolInput::ReadCardChoice(name);

		for (uint32_t idx = 0; idx < cards.size(); idx++) {
			if (cards[idx]->info.ID == card_id) {
				return cards[idx];
			}
		}
		std::cout << "WARNING: invalid card id " << card_id << " !" << std::endl;
	}
}
