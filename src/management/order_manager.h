#pragma once

#include <random>
#include <vector>

#include "../enums/card_age_types.h"


class OrderManager {
public:
	OrderManager();
	OrderManager(const int random_seed);

	const std::vector<uint32_t>& getVisibleCoinIDs() const;
	const std::vector<uint32_t>& getCardIDs(const CardAgeType age) const;
private:
	void randomlySelect(
		std::vector<uint32_t>& container,
		const uint32_t start_id, 
		const uint32_t end_id, 
		const uint32_t number_to_select);

	void randomInitialization();

	bool is_random;
	std::random_device rd;
	std::mt19937 engine;
	
	std::vector<uint32_t> visible_coin_IDs;
	std::vector<uint32_t> first_card_IDs;
	std::vector<uint32_t> second_card_IDs;
	std::vector<uint32_t> third_card_IDs;
};
