#include "game_manager.h"

#include <iostream>

#include "../display/deck_displayer.h"
#include "../display/player_displayer.h"
#include "../enums/card_colors.h"
#include "../io/consol_input.h"
#include "../player/consol_player.h"
#include "../player/robot_player.h"


GameManager::GameManager(Game& game_ref, const OrderManager& order_manager) :
	game(game_ref),
	winner(NO_PLAYER),
	players(2),
	victory_points(NUMBER_OF_PLAYERS, 0)
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

	if (game.age == FIRST_AGE) {
		game.deck.prepareTheSecondAge(); 
		game.age = SECOND_AGE; 
		return true;
	} else if (game.age == SECOND_AGE) {
		game.deck.prepareTheThirdAge();
		game.age = THIRD_AGE;
		return true;
	}

	return false;
}

void GameManager::showTable() const
{
	DeckDisplayer::Show(game.age, game.deck.getCurrentDeck());
	PlayerDisplayer::Show(players[SIMON], game);
	PlayerDisplayer::Show(players[ENIKO], game);
	std::cout << std::endl;
}

void GameManager::handleTurn()
{
	showTable();
	playerAction(players[current_player]);
	playerSwap();
}

void GameManager::declareWinner()
{
	if (winner != NO_PLAYER) {
		announceWinner(winner);
	}

	handleGuildVictoryPoints(SIMON);
	handleGuildVictoryPoints(ENIKO);

	countVictoryPoints(SIMON);
	countVictoryPoints(ENIKO);

	if (victory_points[SIMON] > victory_points[ENIKO]) {
		announceWinner(SIMON);
	} else if (victory_points[SIMON] < victory_points[ENIKO]) {
		announceWinner(ENIKO);
	} else if (players[SIMON]->blue_points > players[ENIKO]->blue_points) {
		announceWinner(SIMON);
	} else if (players[SIMON]->blue_points < players[ENIKO]->blue_points) {
		announceWinner(ENIKO);
	} else {
		std::cout << "Good game! It is a DRAW!" << std::endl;
	}
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
	while (! action.isDone()) {
		action = player->play(game);
		if (action.action_type == SHOW_TABLE) {
			showTable();
		}
	}
	handleAction(player, action);
}

void GameManager::handleAction(std::unique_ptr<Player>& player, const PlayerAction& action)
{
	game.deck.markCard(action.card);
	if (action.action_type == TAKE) {
		game.bank.collectFrom(player->ID, game.getPriceFor(*player, action.card));
		handleCardColor(player, action.card);
		handleCardGain(player, action.card);
	} 
	else if (action.action_type == DISCARD) {
		game.deck.discardCard(action.card);
		game.bank.exchangeCard(player->ID);
	} 
	else {
		// TODO: build a wonder
	}
}

void GameManager::handleCardColor(std::unique_ptr<Player>& player, std::shared_ptr<const Card> card)
{
	switch (card->info.color) {
		case BROWN: player->brown_cards.push_back(card); break;
		case GREY: player->grey_cards.push_back(card); break;
		case YELLOW: game.bank.increaseExchangeRateFor(player->ID); break;
		case RED: game.table.attack(current_player, next_player, game.bank, card->gain.military_point); break;
		case BLUE: player->blue_points += card->gain.victory_point; break;
	}

	if (card->info.color == GREEN) {
		if (player->hasScienceSymbol(card->gain.science_symbol)) {
			handleProgressCoinPick(player);
		} else {
			player->addScienceSymbol(card->gain.science_symbol);
		}
	} else if (card->info.color == PURPLE) {
		player->guild_cards.push_back(card);
		handleGuildMoney(card->gain.guild_action);
	}

	player->card_counter[card->info.color]++;
}

void GameManager::handleCardGain(std::unique_ptr<Player>& player, std::shared_ptr<const Card> card)
{
	game.bank.payTo(player->ID, card->gain.money);
	player->victory_points += card->gain.victory_point;
	player->addChainSymbol(card->gain.chain_symbol);

	if (card->gain.production_deal) {
		game.market.productionDeal(player->ID, card->gain.materials);
	} else if (card->gain.hybrid_production) {
		game.market.hybridProduction(player->ID, card->gain.materials);
	} else {
		game.market.productionChange(player->ID, card->gain.materials);
	}

	switch (card->gain.action) {
		case WONDER_MONEY: game.bank.payTo(player->ID, (player->getNumberOfBuiltWonders() * 2)); break;
		case BROWN_MONEY: game.bank.payTo(player->ID, (player->card_counter[BROWN] * 2)); break;
		case GREY_MONEY: game.bank.payTo(player->ID, (player->card_counter[GREY] * 3)); break;
		case YELLOW_MONEY: game.bank.payTo(player->ID, (player->card_counter[YELLOW] * 1)); break;
		case RED_MONEY: game.bank.payTo(player->ID, (player->card_counter[RED] * 1)); break;
	}
}

void GameManager::handleGuildMoney(const GuildAction action)
{
	if (action == BROWN_GREY_POINT) {
		uint32_t counter_SIMON = players[SIMON]->card_counter[BROWN] + players[SIMON]->card_counter[GREY];
		uint32_t counter_ENIKO = players[ENIKO]->card_counter[BROWN] + players[ENIKO]->card_counter[GREY];
		if (counter_SIMON > counter_ENIKO) {
			game.bank.payTo(SIMON, counter_SIMON);
		}
		else if (counter_SIMON < counter_ENIKO) {
			game.bank.payTo(ENIKO, counter_ENIKO);
		}

	} else {
		switch (action) {
			case YELLOW_POINT: addGuildMoneyForCard(YELLOW); break;
			case RED_POINT: addGuildMoneyForCard(RED); break;
			case GREEN_POINT: addGuildMoneyForCard(GREEN); break;
			case BLUE_POINT: addGuildMoneyForCard(BLUE); break;
		}
	}
}

void GameManager::addGuildMoneyForCard(const CardColor card_color)
{
	if (players[SIMON]->card_counter[card_color] > players[ENIKO]->card_counter[card_color]) {
		game.bank.payTo(SIMON, players[SIMON]->card_counter[card_color]);
	}
	else if (players[SIMON]->card_counter[card_color] < players[ENIKO]->card_counter[card_color]) {
		game.bank.payTo(ENIKO, players[ENIKO]->card_counter[card_color]);
	}
}

void GameManager::handleGuildVictoryPoints(const PlayerID player_id)
{
	for (std::shared_ptr<const Card> guild_card : players[player_id]->guild_cards) {
		if (guild_card->gain.guild_action == MONEY_POINT) {
			if (game.bank.creditInfo(SIMON) > game.bank.creditInfo(ENIKO)) {
				players[SIMON]->victory_points += (game.bank.creditInfo(SIMON) / 3);
			} else if (game.bank.creditInfo(SIMON) < game.bank.creditInfo(ENIKO)) {
				players[ENIKO]->victory_points += (game.bank.creditInfo(ENIKO) / 3);
			}

		} else if (guild_card->gain.guild_action == WONDER_POINT) {
			if (players[SIMON]->getNumberOfBuiltWonders() > players[ENIKO]->getNumberOfBuiltWonders()) {
				players[SIMON]->victory_points += (players[SIMON]->getNumberOfBuiltWonders() * 2);
			} else if (players[SIMON]->getNumberOfBuiltWonders() < players[ENIKO]->getNumberOfBuiltWonders()) {
				players[ENIKO]->victory_points += (players[ENIKO]->getNumberOfBuiltWonders() * 2);
			}

		} else if (guild_card->gain.guild_action == BROWN_GREY_POINT) {
			uint32_t counter_SIMON = players[SIMON]->card_counter[BROWN] + players[SIMON]->card_counter[GREY];
			uint32_t counter_ENIKO = players[ENIKO]->card_counter[BROWN] + players[ENIKO]->card_counter[GREY];
			if (counter_SIMON > counter_ENIKO) {
				players[SIMON]->victory_points += counter_SIMON;
			} else if (counter_SIMON < counter_ENIKO) {
				players[ENIKO]->victory_points += counter_ENIKO;
			}

		} else {
			switch (guild_card->gain.guild_action) {
				case YELLOW_POINT: addGuildVictoryPointsForCard(YELLOW); break;
				case RED_POINT: addGuildVictoryPointsForCard(RED); break;
				case GREEN_POINT: addGuildVictoryPointsForCard(GREEN); break;
				case BLUE_POINT: addGuildVictoryPointsForCard(BLUE); break;
			}
		}
	}
}

void GameManager::addGuildVictoryPointsForCard(const CardColor card_color)
{
	if (players[SIMON]->card_counter[card_color] > players[ENIKO]->card_counter[card_color]) {
		players[SIMON]->victory_points += players[SIMON]->card_counter[card_color];
	}
	else if (players[SIMON]->card_counter[card_color] < players[ENIKO]->card_counter[card_color]) {
		players[ENIKO]->victory_points += players[ENIKO]->card_counter[card_color];
	}
}

void GameManager::handleProgressCoinPick(std::unique_ptr<Player>& player)
{
	// TODO
}

void GameManager::checkForWinner()
{
	if (game.table.isMilitaryWinner(SIMON)) {
		winner = SIMON;
	} else if (game.table.isMilitaryWinner(ENIKO)) {
		winner = ENIKO;
	} else if (players[SIMON]->science_symbols.size() > 5) {
		winner = SIMON;
	} else if (players[ENIKO]->science_symbols.size() > 5) {
		winner = ENIKO;
	}

	if (winner != NO_PLAYER) {
		declareWinner();
	}
}

void GameManager::countVictoryPoints(const PlayerID player_id)
{
	victory_points[player_id] += players[player_id]->victory_points;
	victory_points[player_id] += game.table.getMilitaryVictoryPoints(player_id);
	victory_points[player_id] += game.bank.getMoneyVictoryPoints(player_id);
}

void GameManager::announceWinner(const PlayerID player_id) const
{
	std::cout << "Congratulations! " << players[player_id]->name << " WON!" << std::endl;
}
