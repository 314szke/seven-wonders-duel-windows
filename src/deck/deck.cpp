#include "deck.h"

#include "../constants.h"
#include "../enums/card_age_types.h"
#include "../enums/card_states.h"
#include "../enums/exception_types.h"


Deck::Deck(const OrderManager& order_manager) :
	first_age_card_IDs(order_manager.getCardIDs(FIRST_AGE)),
	second_age_card_IDs(order_manager.getCardIDs(SECOND_AGE)),
	third_age_card_IDs(order_manager.getCardIDs(THIRD_AGE)),
//
	first_age_idx(0),
	second_age_idx(0),
	third_age_idx(0),
//
	number_of_cards_taken(0)
{}

void Deck::prepareTheFirstAge()
{
	prepareAge();
	std::vector<std::shared_ptr<Card>> tmp_first_row;
	std::vector<std::shared_ptr<Card>> tmp_last_row;

	fillVector(tmp_first_row, 6, FIRST_AGE, CARD_VISIBLE);
	fillConstVector(first_row_cards, tmp_first_row);
	
	tmp_last_row = arrangeCardPyramid(tmp_first_row, FIRST_AGE, 5, 2);
	fillConstVector(last_row_cards, tmp_last_row);
	fillConstVector(visible_cards, tmp_first_row);
}

void Deck::prepareTheSecondAge()
{
	prepareAge();
	std::vector<std::shared_ptr<Card>> tmp_first_row;
	std::vector<std::shared_ptr<Card>> tmp_last_row;
	
	fillVector(tmp_first_row, 2, SECOND_AGE, CARD_VISIBLE);
	fillConstVector(first_row_cards, tmp_first_row);

	tmp_last_row = arrangeCardInversePyramid(tmp_first_row, SECOND_AGE, 3, 6);
	fillConstVector(last_row_cards, tmp_last_row);
	fillConstVector(visible_cards, tmp_first_row);
}

void Deck::prepareTheThirdAge()
{
	prepareAge();
	std::vector<std::shared_ptr<Card>> tmp_first_row;
	std::vector<std::shared_ptr<Card>> tmp_last_row;

	// Inverse pyramid section
	fillVector(tmp_first_row, 2, THIRD_AGE, CARD_VISIBLE);
	std::vector<std::shared_ptr<Card>> previous_row = arrangeCardInversePyramid(tmp_first_row, THIRD_AGE, 3, 4);

	// Middle section
	std::vector<std::shared_ptr<Card>> middle_row;
	fillVector(middle_row, 2, THIRD_AGE, CARD_HIDDEN);
	std::vector<std::shared_ptr<Card>> next_row;
	fillVector(next_row, 4, THIRD_AGE, CARD_VISIBLE_UNAVAILABLE);
	arrangeThirdAgeMiddleSection(previous_row, middle_row, next_row);

	// Pyramid section
	tmp_last_row = arrangeCardPyramid(next_row, THIRD_AGE, 3, 2);
	fillConstVector(last_row_cards, tmp_last_row);
	fillConstVector(visible_cards, tmp_first_row);
}

const std::vector<std::shared_ptr<const Card>>& Deck::getCurrentDeck() const
{
	return last_row_cards;
}

const std::vector<std::shared_ptr<const Card>>& Deck::getVisibleCards() const
{
	return visible_cards;
}

const std::vector<std::shared_ptr<const Card>>& Deck::getDiscardedCards() const
{
	return discard_pile;
}

std::shared_ptr<const Card> Deck::getCard(const uint32_t card_id) const
{
	return card_loader.getCard(card_id);
}

std::shared_ptr<const Card> Deck::getVisibleCard(const uint32_t card_id) const
{
	std::shared_ptr<const Card> card = getCard(card_id);
	if (card->state != CARD_VISIBLE) {
		throw CARD_INVALID_STATE;
	}
	return card;
}

void Deck::markCard(std::shared_ptr<const Card> selected_card)
{
	std::shared_ptr<Card> card = card_loader.getCard(selected_card->info.ID);

	if (card->state != CARD_VISIBLE) {
		throw CARD_INVALID_STATE;
	}

	card->state = CARD_TAKEN;
	number_of_cards_taken++;

	makeParentVisible(card->parent_left);
	makeParentVisible(card->parent_right);
}

void Deck::discardCard(std::shared_ptr<const Card> selected_card)
{
	discard_pile.push_back(selected_card);
}

bool Deck::isAgeOn() const
{
	if (number_of_cards_taken >= NUMBER_OF_CARDS_PER_AGE) {
		return false;
	}
	return true;
}

void Deck::prepareAge()
{
	number_of_cards_taken = 0;

	visible_cards.resize(0);
	first_row_cards.resize(0);
	last_row_cards.resize(0);
}

void Deck::fillVector(
	std::vector<std::shared_ptr<Card>>& container, 
	const uint32_t card_number, 
	const CardAgeType card_age, 
	const CardState card_state)
{
	switch (card_age) {
		case FIRST_AGE: fillVector(container, card_number, card_state, first_age_card_IDs, &first_age_idx); break;
		case SECOND_AGE: fillVector(container, card_number, card_state, second_age_card_IDs, &second_age_idx); break;
		case THIRD_AGE: fillVector(container, card_number, card_state, third_age_card_IDs, &third_age_idx); break;
		default: throw DECK_NOT_FOUND;
	}
}

void Deck::fillVector(
	std::vector<std::shared_ptr<Card>>& container, 
	const uint32_t card_number, 
	const CardState card_state, 
	const std::vector<uint32_t>& card_IDs, 
	uint32_t* idx)
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

void Deck::fillConstVector(std::vector<std::shared_ptr<const Card>>& const_row, const std::vector<std::shared_ptr<Card>>& tmp_row)
{
	for (std::shared_ptr<Card> card_ptr : tmp_row) {
		const_row.push_back(card_ptr);
	}
}

std::vector<std::shared_ptr<Card>> Deck::arrangeCardPyramid(
	const std::vector<std::shared_ptr<Card>>& init_previous_row,
	const CardAgeType card_age, 
	const uint32_t start, 
	const uint32_t end)
{
	std::vector<std::shared_ptr<Card>> previous_row = init_previous_row;
	std::vector<std::shared_ptr<Card>> current_row;

	bool face_up = false;

	for (uint32_t cards_per_row = start; cards_per_row >= end; cards_per_row--) {
		current_row.resize(0);
	
		if (face_up) {
			fillVector(current_row, cards_per_row, card_age, CARD_VISIBLE_UNAVAILABLE);
		} else {
			fillVector(current_row, cards_per_row, card_age, CARD_HIDDEN);
		}
		face_up = !face_up;

		for (uint32_t idx = 0; idx < previous_row.size(); idx++) {
			if (idx != 0) {
				previous_row[idx]->parent_left = current_row[(idx - 1)];
			}
			if (idx < (previous_row.size() - 1)) {
				previous_row[idx]->parent_right = current_row[idx];
				current_row[idx]->child_left = previous_row[idx];
				current_row[idx]->child_right = previous_row[(idx + 1)];
			}
		}

		previous_row = current_row;
	}

	return current_row;
}

std::vector<std::shared_ptr<Card>> Deck::arrangeCardInversePyramid(
	const std::vector<std::shared_ptr<Card>>& init_previous_row,
	const CardAgeType card_age, 
	const uint32_t start, 
	const uint32_t end)
{
	std::vector<std::shared_ptr<Card>> previous_row = init_previous_row;
	std::vector<std::shared_ptr<Card>> current_row;

	bool face_up = false;

	for (uint32_t cards_per_row = start; cards_per_row <= end; cards_per_row++) {
		current_row.resize(0);
	
		if (face_up) {
			fillVector(current_row, cards_per_row, card_age, CARD_VISIBLE_UNAVAILABLE);
		}
		else {
			fillVector(current_row, cards_per_row, card_age, CARD_HIDDEN);
		}
		face_up = !face_up;

		for (uint32_t idx = 0; idx < current_row.size(); idx++) {
			if (idx != 0) {
				current_row[idx]->child_left = previous_row[(idx - 1)];
				previous_row[(idx - 1)]->parent_right = current_row[idx];
			}
			if (idx < (current_row.size() - 1)) {
				current_row[idx]->child_right = previous_row[idx];
				previous_row[idx]->parent_left = current_row[idx];
			}
		}

		previous_row = current_row;
	}

	return current_row;
}

void Deck::arrangeThirdAgeMiddleSection(
	const std::vector<std::shared_ptr<Card>>& previous_row, 
	const std::vector<std::shared_ptr<Card>>& middle_row, 
	const std::vector<std::shared_ptr<Card>>& next_row)
{
	// First middle card
	previous_row[0]->parent_right = middle_row[0];
	previous_row[1]->parent_left = middle_row[0];

	middle_row[0]->child_left = previous_row[0];
	middle_row[0]->child_right = previous_row[1];

	middle_row[0]->parent_left = next_row[0];
	middle_row[0]->parent_right = next_row[1];

	next_row[0]->child_right = middle_row[0];
	next_row[1]->child_left = middle_row[0];

	// Second middle card
	previous_row[2]->parent_right = middle_row[1];
	previous_row[3]->parent_left = middle_row[1];

	middle_row[1]->child_left = previous_row[2];
	middle_row[1]->child_right = previous_row[3];

	middle_row[1]->parent_left = next_row[2];
	middle_row[1]->parent_right = next_row[3];

	next_row[2]->child_right = middle_row[1];
	next_row[3]->child_left = middle_row[1];
}

void Deck::makeParentVisible(std::shared_ptr<Card> parent)
{
	if (parent == NULL) {
		return;
	}

	if ((parent->child_left != NULL) && (parent->child_left->state != CARD_TAKEN)) {
		return;
	}
	
	if ((parent->child_right != NULL) && (parent->child_right->state != CARD_TAKEN)) {
		return;
	}
	
	parent->state = CARD_VISIBLE;
	for (uint32_t idx = 0; idx < visible_cards.size(); idx++) {
		if (visible_cards[idx]->state == CARD_TAKEN) {
			visible_cards[idx] = parent;
			return;
		}
	}

	visible_cards.push_back(parent);
}
