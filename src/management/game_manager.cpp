#include "game_manager.h"

#include <iostream>


GameManager::GameManager() :
	random_seed(19),
	order_manger(random_seed),
	deck(order_manger),
	table(order_manger.getVisibleCoinIDs())
{}

void GameManager::setTheFirstStage()
{
	deck.prepareTheFirstAge();
}

void GameManager::setTheSecondStage()
{
	deck.prepareTheSecondAge();
}

void GameManager::setTheThirdStage()
{
	deck.prepareTheThirdAge();
}

bool GameManager::gameIsOn()
{
	if (deck.isAgeOn()) {
		return true;
	}

	switch (deck.getCurrentAge()) {
		case FIRST_AGE: deck.prepareTheSecondAge(); break;
		case SECOND_AGE: deck.prepareTheThirdAge(); break;
		case THIRD_AGE: return false;
	}
}

void GameManager::showTable()
{
	deck.displayDeck();
}

void GameManager::takeCardFromConsol(const uint32_t consol_card_id)
{
	int card_id = consol_card_id - 1;
	int visibility_list_id = -1;

	const std::vector<Card*>& visible_cards = deck.getVisibleCards();
	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->info.ID == card_id) {
			visibility_list_id = idx;
			deck.takeCard(idx);
			return;
		}
	}
	
	std::cout << "WARNING: invalid card id << " << consol_card_id << ">> !" << std::endl << std::endl;
}
