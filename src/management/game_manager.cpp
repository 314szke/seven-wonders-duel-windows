#include "game_manager.h"

#include <iostream>

#include "../display/card_displayer.h"
#include "../display/deck_displayer.h"
#include "../display/player_displayer.h"
#include "../enums/card_colors.h"
#include "../io/consol_input.h"
#include "../player/consol_player.h"
#include "../player/robot_player.h"


GameManager::GameManager(Game& game_ref, const OrderManager& order_manager) :
	game(game_ref),
	players(2)
{
	current_player = order_manager.getInitialPlayerOrder()[0];
	next_player = order_manager.getInitialPlayerOrder()[1];
}

void GameManager::initalizeGame()
{
	initializePlayer(SIMON);
	initializePlayer(ENIKO);
	game.deck.prepareTheFirstAge();
}

bool GameManager::gameIsOn() const
{
	if (game.deck.isAgeOn()) {
		return true;
	}

	switch (game.age) {
		case FIRST_AGE: game.deck.prepareTheSecondAge(); game.age = SECOND_AGE; return true;
		case SECOND_AGE: game.deck.prepareTheThirdAge(); game.age = THIRD_AGE; return true;
	}

	return false;
}

void GameManager::showTable() const
{
	DeckDisplayer::Show(game.age, game.deck.getCurrentDeck());
	PlayerDisplayer::Show(players[SIMON], game);
	PlayerDisplayer::Show(players[ENIKO], game);
}

void GameManager::handleTurn()
{
	showTable();
	playerAction(players[current_player]);
	playerSwap();
}

void GameManager::initializePlayer(const PlayerID player_id)
{
	switch (ConsolInput::ReadPlayerOption(player_id)) {
		case CONSOL_PLAYER: {
			players[player_id].reset(
				new ConsolPlayer(player_id, ConsolInput::ReadPlayerName(player_id)));
			break;
		}
		case ROBOT_PLAYER: {
			players[player_id].reset(
				new RobotPlayer(player_id, ConsolInput::ReadPlayerName(player_id)));
			break;
		}
	}
}

void GameManager::playerSwap()
{
	PlayerID id = current_player;
	current_player = next_player;
	next_player = id;
}

void GameManager::playerAction(std::unique_ptr<Player>& player)
{
	PlayerAction action;
	while (action.isNotDone()) {
		action = player->play(game);

		if (action.action_type == INFO) {
			CardDisplayer::Show(action.card);
		}
	}
	game.deck.takeCard(action.card);

	if (action.action_type == TAKE) {
		game.bank.collectFrom(player->ID, game.getPriceFor(*player, action.card));
		handleCard(player, action.card);
	} else if (action.action_type == DISCARD) {
		game.bank.exchangeCard(player->ID);
	} else {
		// TODO: build a wonder
	}
}

void GameManager::handleCard(std::unique_ptr<Player>& player, std::shared_ptr<const Card> card)
{
	if (card->info.color == BROWN) {
		player->brown_cards.push_back(card);
	} else if (card->info.color == GREY) {
		player->grey_cards.push_back(card);
	} else if (card->info.color == YELLOW) {
		game.bank.increaseExchangeRateFor(player->ID);
	}
	
	game.bank.payTo(player->ID, card->gain.money);
	player->victory_points += card->gain.victory_point;
	if (card->gain.military_point > 0) {
		game.table.attack(current_player, next_player, game.bank, card->gain.military_point);
	}

	if (card->gain.chain_symbol != NO_CHAIN) {
		player->chain_symbols.push_back(card->gain.chain_symbol);
	}	
	if (card->gain.science_symbol != NO_SCIENCE) {
		player->science_symbols.push_back(card->gain.science_symbol);
	}

	if (card->gain.production_deal) {
		game.market.productionDeal(player->ID, card->gain.materials);
	} else if (card->gain.hybrid_production) {
		game.market.hybridProduction(player->ID, card->gain.materials);
	} else {
		game.market.productionChange(player->ID, card->gain.materials);
	}
}
