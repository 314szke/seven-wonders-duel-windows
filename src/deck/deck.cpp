#include "deck.h"

#include "../constants.h"
#include "../enums/card_age_types.h"
#include "../enums/card_states.h"
#include "../enums/exception_types.h"


Deck::Deck(const OrderManager& order_manager) :
	current_age(NO_AGE),
	card_manager(order_manager)
{}

void Deck::prepareTheFirstAge()
{
	current_age = FIRST_AGE;
	card_manager.fill(first_row_cards, 6, FIRST_AGE, CARD_VISIBLE);
	last_row_cards = arrangeCardPyramid(first_row_cards, FIRST_AGE, 5, 2);
	visible_cards = first_row_cards;
}

void Deck::prepareTheSecondAge()
{
	current_age = SECOND_AGE;
	card_manager.fill(first_row_cards, 2, SECOND_AGE, CARD_VISIBLE);
	last_row_cards = arrangeCardInversePyramid(first_row_cards, SECOND_AGE, 3, 6);
	visible_cards = first_row_cards;
}

void Deck::prepareTheThirdAge()
{
	current_age = THIRD_AGE;

	// Inverse pyramid section
	card_manager.fill(first_row_cards, 2, THIRD_AGE, CARD_VISIBLE);
	std::vector<Card*> previous_row = arrangeCardInversePyramid(first_row_cards, THIRD_AGE, 3, 4);

	// Middle section
	std::vector<Card*> middle_row;
	card_manager.fill(middle_row, 2, THIRD_AGE, CARD_HIDDEN);
	std::vector<Card*> next_row;
	card_manager.fill(next_row, 4, THIRD_AGE, CARD_VISIBLE_UNAVAILABLE);
	arrangeThirdAgeMiddleSection(previous_row, middle_row, next_row);

	// Pyramid section
	last_row_cards = arrangeCardPyramid(next_row, THIRD_AGE, 3, 2);
	visible_cards = first_row_cards;
}

void Deck::displayDeck()
{
	deck_displayer.show(current_age, first_row_cards, last_row_cards);
}

const std::vector<Card*>& Deck::getVisibleCards() const
{
	return visible_cards;
}

void Deck::takeCard(const uint32_t visible_card_idx)
{
	visible_cards[visible_card_idx]->state = CARD_TAKEN;

	Card* parent_left = visible_cards[visible_card_idx]->parent_left;
	Card* parent_right = visible_cards[visible_card_idx]->parent_right;

	makeParentVisible(parent_left);
	makeParentVisible(parent_right);
}

std::vector<Card*> Deck::arrangeCardPyramid(
	const std::vector<Card*>& init_previous_row, 
	const CardAgeType card_age, 
	const uint32_t start, 
	const uint32_t end)
{
	std::vector<Card*> previous_row = init_previous_row;
	std::vector<Card*> current_row;

	bool face_up = false;

	for (uint32_t cards_per_row = start; cards_per_row >= end; cards_per_row--) {
		current_row.resize(0);
	
		if (face_up) {
			card_manager.fill(current_row, cards_per_row, card_age, CARD_VISIBLE_UNAVAILABLE);
		} else {
			card_manager.fill(current_row, cards_per_row, card_age, CARD_HIDDEN);
		}
		face_up = !face_up;

		for (uint32_t idx = 0; idx < cards_per_row; idx++) {
			previous_row[idx]->parent_right = current_row[idx];
			if (idx != 0) {
				previous_row[idx]->parent_left = current_row[(idx - 1)];
			}
			current_row[idx]->child_left = previous_row[idx];
			current_row[idx]->child_right = previous_row[(idx + 1)];
		}

		previous_row = current_row;
	}

	return current_row;
}

std::vector<Card*> Deck::arrangeCardInversePyramid(
	const std::vector<Card*>& init_previous_row, 
	const CardAgeType card_age, 
	const uint32_t start, 
	const uint32_t end)
{
	std::vector<Card*> previous_row = init_previous_row;
	std::vector<Card*> current_row;

	bool face_up = false;

	for (uint32_t cards_per_row = start; cards_per_row <= end; cards_per_row++) {
		current_row.resize(0);
	
		if (face_up) {
			card_manager.fill(current_row, cards_per_row, card_age, CARD_VISIBLE_UNAVAILABLE);
		}
		else {
			card_manager.fill(current_row, cards_per_row, card_age, CARD_HIDDEN);
		}
		face_up = !face_up;

		for (uint32_t idx = 0; idx < cards_per_row; idx++) {
			if (idx < (cards_per_row - 1)) {
				current_row[idx]->child_right = previous_row[idx];
				previous_row[idx]->parent_left = current_row[idx];
			}
			if (idx != 0) {
				current_row[idx]->child_left = previous_row[(idx - 1)];
				previous_row[(idx - 1)]->parent_right = current_row[idx];
			}
		}

		previous_row = current_row;
	}

	return current_row;
}

void Deck::arrangeThirdAgeMiddleSection(std::vector<Card*>& previous_row, std::vector<Card*>& middle_row, std::vector<Card*>& next_row)
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

void Deck::makeParentVisible(Card* parent)
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

	throw DECK_TOO_MANY_VISIBLE_CARDS;
}
