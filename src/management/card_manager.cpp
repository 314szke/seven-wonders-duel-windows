#include "card_manager.h"

#include "../constants.h"
#include "../enums/card_age_types.h"
#include "../enums/exception_types.h"


CardManager::CardManager(const OrderManager& order_manager) :
	first_age_card_IDs(order_manager.getCardIDs(FIRST_AGE)),
	second_age_card_IDs(order_manager.getCardIDs(SECOND_AGE)),
	third_age_card_IDs(order_manager.getCardIDs(THIRD_AGE)),
//
	first_idx(0),
	second_idx(0),
	third_idx(0)
{}

void CardManager::fill(
	std::vector<std::shared_ptr<Card>>& container,
	const uint32_t card_number, 
	const CardAgeType card_age, 
	const CardState card_state)
{
	switch (card_age) {
		case FIRST_AGE: fill(container, card_number, card_state, first_age_card_IDs, &first_idx); break;
		case SECOND_AGE: fill(container, card_number, card_state, second_age_card_IDs, &second_idx); break;
		case THIRD_AGE: fill(container, card_number, card_state, third_age_card_IDs, &third_idx); break;
		default: throw DECK_NOT_FOUND;
	}
}

std::shared_ptr<const Card> CardManager::getCard(const uint32_t card_id) const
{
	return card_loader.getCard(card_id);
}

std::shared_ptr<Card> CardManager::getCard(const uint32_t card_id)
{
	return card_loader.getCard(card_id);
}

void CardManager::fill(std::vector<std::shared_ptr<Card>>& container, const uint32_t card_number, const CardState card_state, const std::vector<uint32_t>& card_IDs, uint32_t* idx)
{
	uint32_t end_idx = (*idx + card_number);
	if (end_idx > NUMBER_OF_CARDS_PER_AGE) {
		throw DECK_OUT_OF_CARDS;
	}

	for (; *idx < end_idx; *idx = (*idx + 1)) {
		container.push_back(card_loader.getCard(card_IDs[*idx]));
		container.back()->state = card_state;
	}
}
