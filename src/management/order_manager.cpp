#include "order_manager.h"

#include <algorithm>
#include <random>

#include "../constants.h"
#include "../enums/exception_types.h"


OrderManager::OrderManager() :
	is_random(true),
	engine(rd())
{
	randomInitialization();
}

OrderManager::OrderManager(const int random_seed) :
	is_random(true),
	engine(random_seed)
{
	randomInitialization();
}

const std::vector<PlayerID>& OrderManager::getInitialPlayerOrder() const
{
	return initial_player_order;
}

const std::vector<uint32_t>& OrderManager::getWonderIDs() const
{
	return wonder_IDs;
}

const std::vector<uint32_t>& OrderManager::getVisibleCoinIDs() const
{
	return visible_coin_IDs;
}

const std::vector<uint32_t>& OrderManager::getCardIDs(const CardAgeType age) const
{
	switch (age) {
		case FIRST_AGE: return first_card_IDs;
		case SECOND_AGE: return second_card_IDs;
		case THIRD_AGE: return third_card_IDs;
		default: throw DECK_NOT_FOUND;
	}
}

void OrderManager::randomlySelect(
	std::vector<uint32_t>& container,
	const uint32_t start_id, 
	const uint32_t end_id, 
	const uint32_t number_to_select)
{
	std::vector<uint32_t> all_IDs;
	for (uint32_t id = start_id; id < end_id; id++) {
		all_IDs.push_back(id);
	}
	std::shuffle(all_IDs.begin(), all_IDs.end(), engine);

	for (uint32_t idx = 0; idx < number_to_select; idx++) {
		container.push_back(all_IDs[idx]);
	}
}

void OrderManager::randomInitialization()
{
	initial_player_order = { SIMON, ENIKO };
	std::shuffle(initial_player_order.begin(), initial_player_order.end(), engine);

	for (uint32_t idx = 0; idx < TOTAL_NUMBER_OF_WONDERS; idx++) {
		wonder_IDs.push_back(idx);
	}
	std::shuffle(wonder_IDs.begin(), wonder_IDs.end(), engine);

	int start_idx = 0;
	int end_idx = NUMBER_OF_PROGRESS_COINS;
	randomlySelect(visible_coin_IDs, start_idx, end_idx, NUMBER_OF_VISIBLE_COINS);

	end_idx = NUMBER_OF_FIRST_AGE_CARDS;
	randomlySelect(first_card_IDs, start_idx, end_idx, NUMBER_OF_CARDS_PER_AGE);

	start_idx = end_idx;
	end_idx += NUMBER_OF_SECOND_AGE_CARDS;
	randomlySelect(second_card_IDs, start_idx, end_idx, NUMBER_OF_CARDS_PER_AGE);

	start_idx = end_idx;
	end_idx += NUMBER_OF_THIRD_AGE_CARDS;
	randomlySelect(third_card_IDs, start_idx, end_idx, (NUMBER_OF_CARDS_PER_AGE - NUMBER_OF_GUILD_CARDS_USED));
	
	start_idx = end_idx;
	end_idx += NUMBER_OF_GUILD_CARDS;
	randomlySelect(third_card_IDs, start_idx, end_idx, NUMBER_OF_GUILD_CARDS_USED);
	
	// Shuffle the guild cards into the third deck
	std::shuffle(third_card_IDs.begin(), third_card_IDs.end(), engine);
}