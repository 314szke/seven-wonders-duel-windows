#include "game_manager.h"

#include <iostream>

#include "../display/deck_displayer.h"
#include "../display/player_displayer.h"
#include "../enums/card_colors.h"
#include "../io/consol_input.h"
#include "../player/consol_player.h"
#include "../player/robot_player.h"


GameManager::GameManager(Game& game_ref) :
	game(game_ref),
	current_player(SIMON),
	next_player(ENIKO),
	players(2)
{}

void GameManager::initializePlayers()
{
	initializePlayer(SIMON);
	initializePlayer(ENIKO);
}

void GameManager::initalizeGame()
{
	game.deck.prepareTheFirstAge();
	current_player = SIMON;
	next_player = ENIKO;
}

bool GameManager::gameIsOn() const
{
	if (game.deck.isAgeOn()) {
		return true;
	}

	switch (game.age) {
		case FIRST_AGE: game.deck.prepareTheSecondAge(); game.age = SECOND_AGE; break;
		case SECOND_AGE: game.deck.prepareTheThirdAge(); game.age = THIRD_AGE; break;
		case THIRD_AGE: return false;
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
	playerTakesCard(players[current_player]);
	playerSwap();

	showTable();
	playerTakesCard(players[current_player]);
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

void GameManager::playerTakesCard(std::unique_ptr<Player>& player)
{
	const std::vector<Card*>& cards = game.deck.getVisibleCards();

	int card_id = -1;
	uint32_t price = 0;
	
	while (card_id == -1) {
		card_id = player->play(cards);

		if (! player->hasChainSymbol(cards[card_id]->cost.symbol)) {
			price = game.market.getMaterialBundlePrice(player->ID, cards[card_id]->cost.materials);
			
			if (! game.bank.creditCheck(player->ID, price)) {
				std::cout << "WARNING: " << player->name << " can NOT pay for card " << card_id << "!" << std::endl;
				card_id = -1;
			}
		}
	}
	
	game.deck.takeCard(card_id);
	game.bank.collectFrom(player->ID, price);
	handleCard(player, cards[card_id]);
}

void GameManager::handleCard(std::unique_ptr<Player>& player, const Card* card)
{
	switch (card->info.color) {
		case BROWN: game.market.productionChange(player->ID, card->gain.materials); break;
		case GREY: game.market.productionDeal(player->ID, card->gain.materials); break;
	}
}
