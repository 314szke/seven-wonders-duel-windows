#pragma once

#include <vector>

#include "../deck/card.h"
#include "../io/card_loader.h"
#include "../management/order_manager.h"


class CardManager {
public:
	CardManager(const OrderManager& order_manager);

	void reset();

	void fill(
		std::vector<Card*>& container,
		const uint32_t card_number,
		const CardAgeType card_age,
		const CardState card_state);

private:
	void fill(
		std::vector<Card*>& container,
		const uint32_t card_number,
		const CardState card_state,
		const std::vector<uint32_t>& card_IDs,
		uint32_t* idx);

	const std::vector<uint32_t>& first_age_card_IDs;
	const std::vector<uint32_t>& second_age_card_IDs;
	const std::vector<uint32_t>& third_age_card_IDs;

	uint32_t first_idx;
	uint32_t second_idx;
	uint32_t third_idx;

	CardLoader card_loader;
};
