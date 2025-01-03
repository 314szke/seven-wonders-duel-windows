#include "game_manager.h"


GameManager::GameManager() :
	deck(order_manger),
	table(order_manger.getVisibleCoinIDs())
{}

void GameManager::setTheFirstStage()
{
	deck.prepareTheFirstAge();
	deck.displayDeck();
}

void GameManager::setTheSecondStage()
{
	deck.prepareTheSecondAge();
	deck.displayDeck();
}

void GameManager::setTheThirdStage()
{
	deck.prepareTheThirdAge();
	deck.displayDeck();
}
