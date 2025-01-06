#pragma once

#include <vector>

#include "../deck/card.h"
#include "../enums/card_age_types.h"


class DeckDisplayer {
public:
	static void Show(const CardAgeType card_age, const std::vector<Card*>& last_row_in_deck);
private:
	static void showFirstAge(const std::vector<Card*>& last_row_in_deck);
	static void showSecondAge(const std::vector<Card*>& last_row_in_deck);
	static void showThirdAge(const std::vector<Card*>& last_row_in_deck);

	static uint32_t getLength(const std::vector<Card*>& row);

	static std::vector<Card*> printPyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows);
	static std::vector<Card*> printInversePyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows);
	static void printThirdAgeMiddleRow(const std::vector<Card*>& row);

	static void printRow(const std::vector<Card*>& row);
	static void printCard(const Card* card);
};
