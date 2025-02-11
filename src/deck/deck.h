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

	const std::vector<std::shared_ptr<const Card>>& getCurrentDeck() const;
	const std::vector<std::shared_ptr<const Card>>& getVisibleCards() const;
	std::shared_ptr<const Card> getCard(const uint32_t card_id) const;
	std::shared_ptr<const Card> getVisibleCard(const uint32_t card_id) const;

	void takeCard(std::shared_ptr<const Card> selected_card);
	bool isAgeOn() const;

private:
	void prepareAge();
	void fillConstVector(std::vector<std::shared_ptr<const Card>>& const_row, const std::vector<std::shared_ptr<Card>>& tmp_row);

	std::vector<std::shared_ptr<Card>> arrangeCardPyramid(
		const std::vector<std::shared_ptr<Card>>& init_previous_row,
		const CardAgeType card_age, 
		const uint32_t start, 
		const uint32_t end);
	
	std::vector<std::shared_ptr<Card>> arrangeCardInversePyramid(
		const std::vector<std::shared_ptr<Card>>& init_previous_row,
		const CardAgeType card_age, 
		const uint32_t start, 
		const uint32_t end);
	
	void arrangeThirdAgeMiddleSection(
		const std::vector<std::shared_ptr<Card>>& previous_row,
		const std::vector<std::shared_ptr<Card>>& middle_row,
		const std::vector<std::shared_ptr<Card>>& next_row);

	void makeParentVisible(std::shared_ptr<Card> parent);

	CardManager card_manager;

	// First row is the first row to take cards from
	// Last row is the last row to take cards from
	uint32_t number_of_cards_taken;
	std::vector<std::shared_ptr<const Card>> visible_cards;
	std::vector<std::shared_ptr<const Card>> first_row_cards;
	std::vector<std::shared_ptr<const Card>> last_row_cards;
};
