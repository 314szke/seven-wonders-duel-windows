#pragma once

#include <vector>

#include "../deck/card.h"
#include "../enums/card_age_types.h"


class DeckDisplayer {
public:
	void show(const CardAgeType card_age, const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck);
private:
	void showFirstAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck);
	void showSecondAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck);
	void showThirdAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck);

	uint32_t getLength(const std::vector<Card*>& row);
	uint32_t getEvenLength(const std::vector<Card*>& row);

	std::vector<Card*> printPyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows, const uint32_t max_length);
	std::vector<Card*> printInversePyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows, const uint32_t max_length);
	void printThirdAgeMiddleRow(const std::vector<Card*>& row, const uint32_t max_length);
	void printRow(const std::vector<Card*>& row, const uint32_t max_length);
};
