#include "game_manager.h"

#include <iostream>

#include "../display/deck_displayer.h"
#include "../display/player_displayer.h"
#include "../io/consol_input.h"
#include "../player/consol_player.h"
#include "../player/robot_player.h"


GameManager::GameManager(Game& game_ref) :
	game(game_ref),
	current_player(SIMON),
	next_player(ENIKO)
{}

void GameManager::initializePlayers()
{
	switch (ConsolInput::ReadPlayerOption(SIMON)) {
		case CONSOL_PLAYER: Simon.reset(new ConsolPlayer(SIMON, ConsolInput::ReadPlayerName(SIMON))); break;
		case ROBOT_PLAYER: Simon.reset(new RobotPlayer(SIMON, ConsolInput::ReadPlayerName(SIMON))); break;
	}
	
	switch (ConsolInput::ReadPlayerOption(ENIKO)) {
		case CONSOL_PLAYER: Eniko.reset(new ConsolPlayer(ENIKO, ConsolInput::ReadPlayerName(ENIKO))); break;
		case ROBOT_PLAYER: Eniko.reset(new RobotPlayer(ENIKO, ConsolInput::ReadPlayerName(ENIKO))); break;
	}
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
	PlayerDisplayer::Show(Simon, game);
	PlayerDisplayer::Show(Eniko, game);
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
