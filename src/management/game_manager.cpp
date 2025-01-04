#include "game_manager.h"

#include <iostream>

#include "../io/consol_input.h"
#include "../player/consol_player.h"
#include "../player/robot_player.h"


GameManager::GameManager(Game& game_ref) :
	game(game_ref),
	current_player(SIMON),
	next_player(ENIKO),
	player_displayer(game_ref)
{}

void GameManager::initializePlayers()
{
	switch (ConsolInput::readPlayerOption(SIMON)) {
		case CONSOL_PLAYER: Simon.reset(new ConsolPlayer(SIMON, ConsolInput::readPlayerName(SIMON))); break;
		case ROBOT_PLAYER: Simon.reset(new RobotPlayer(SIMON, ConsolInput::readPlayerName(SIMON))); break;
	}
	
	switch (ConsolInput::readPlayerOption(ENIKO)) {
		case CONSOL_PLAYER: Eniko.reset(new ConsolPlayer(ENIKO, ConsolInput::readPlayerName(ENIKO))); break;
		case ROBOT_PLAYER: Eniko.reset(new RobotPlayer(ENIKO, ConsolInput::readPlayerName(ENIKO))); break;
	}
}

void GameManager::initalizeGame()
{
	game.deck.prepareTheFirstAge();
	current_player = SIMON;
	next_player = ENIKO;
}

bool GameManager::gameIsOn()
{
	if (game.deck.isAgeOn()) {
		return true;
	}

	switch (game.deck.getCurrentAge()) {
		case FIRST_AGE: game.deck.prepareTheSecondAge(); break;
		case SECOND_AGE: game.deck.prepareTheThirdAge(); break;
		case THIRD_AGE: return false;
	}

	return false;
}

void GameManager::showTable()
{
	game.deck.displayDeck();
	player_displayer.show(Simon);
	player_displayer.show(Eniko);
}

void GameManager::handleTurn()
{
	showTable();

	switch (current_player) {
		case SIMON: {
			handleCard(Simon, Simon->play(game.deck.getVisibleCards()));
			handleCard(Eniko, Eniko->play(game.deck.getVisibleCards()));
			break;
		}
		case ENIKO: {
			handleCard(Eniko, Eniko->play(game.deck.getVisibleCards())); 
			handleCard(Simon, Simon->play(game.deck.getVisibleCards())); 
			break;
		}
	}
}

void GameManager::handleCard(std::unique_ptr<Player>& player, const uint32_t card_id)
{
	game.deck.takeCard(card_id);
}
