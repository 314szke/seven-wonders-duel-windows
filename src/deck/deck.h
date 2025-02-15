#pragma once

#include <vector>

#include "../deck/card.h"
#include "../io/card_loader.h"
#include "../management/order_manager.h"


class Deck {
public:
	Deck(const OrderManager& order_manager);

	void prepareTheFirstAge();
	void prepareTheSecondAge();
	void prepareTheThirdAge();

	const std::vector<std::shared_ptr<const Card>>& getCurrentDeck() const;
	const std::vector<std::shared_ptr<const Card>>& getVisibleCards() const;
	const std::vector<std::shared_ptr<const Card>>& getDiscardedCards() const;

	std::shared_ptr<const Card> getCard(const uint32_t card_id) const;
	std::shared_ptr<const Card> getVisibleCard(const uint32_t card_id) const;

	void markCard(std::shared_ptr<const Card> selected_card);
	void discardCard(std::shared_ptr<const Card> selected_card);

	bool isAgeOn() const;

private:
	void prepareAge();

	void fillVector(
		std::vector<std::shared_ptr<Card>>& container,
		const uint32_t card_number,
		const CardAgeType card_age,
		const CardState card_state);

	void fillVector(
		std::vector<std::shared_ptr<Card>>& container,
		const uint32_t card_number,
		const CardState card_state,
		const std::vector<uint32_t>& card_IDs,
		uint32_t* idx);

	void fillConstVector(
		std::vector<std::shared_ptr<const Card>>& const_row, 
		const std::vector<std::shared_ptr<Card>>& tmp_row);

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


	CardLoader card_loader;

	const std::vector<uint32_t>& first_age_card_IDs;
	const std::vector<uint32_t>& second_age_card_IDs;
	const std::vector<uint32_t>& third_age_card_IDs;

	uint32_t first_age_idx;
	uint32_t second_age_idx;
	uint32_t third_age_idx;

	// First row is the first row to take cards from
	// Last row is the last row to take cards from
	uint32_t number_of_cards_taken;
	std::vector<std::shared_ptr<const Card>> visible_cards;
	std::vector<std::shared_ptr<const Card>> first_row_cards;
	std::vector<std::shared_ptr<const Card>> last_row_cards;

	std::vector <std::shared_ptr<const Card>> discard_pile;
};
