#pragma once

#include <vector>

#include "card.h"
#include "../management/card_manager.h"
#include "../management/order_manager.h"


class Deck {
public:
	Deck(const OrderManager& order_manager);

	void prepareTheFirstAge();
	void prepareTheSecondAge();
	void prepareTheThirdAge();

	const std::vector<Card*>& getCurrentDeck() const;
	const std::vector<Card*>& getVisibleCards() const;
	void takeCard(const uint32_t visible_card_idx);

	bool isAgeOn() const;

private:
	void prepareAge();

	std::vector<Card*> arrangeCardPyramid(
		const std::vector<Card*>& init_previous_row,
		const CardAgeType card_age, 
		const uint32_t start, 
		const uint32_t end);
	
	std::vector<Card*> arrangeCardInversePyramid(
		const std::vector<Card*>& init_previous_row,
		const CardAgeType card_age, 
		const uint32_t start, 
		const uint32_t end);
	
	void arrangeThirdAgeMiddleSection(
		std::vector<Card*>& previous_row, 
		std::vector<Card*>& middle_row, 
		std::vector<Card*>& next_row);

	void makeParentVisible(Card* parent);

	CardManager card_manager;

	// First row is the first row to take cards from
	// Last row is the last row to take cards from
	uint32_t number_of_cards_taken;
	std::vector<Card*> visible_cards;
	std::vector<Card*> first_row_cards;
	std::vector<Card*> last_row_cards;
};
