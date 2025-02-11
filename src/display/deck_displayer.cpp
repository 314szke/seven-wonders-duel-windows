#include "deck_displayer.h"

#include <iostream> 

#include "../enums/exception_types.h"


constexpr auto NUMBER_OF_ROWS = 5;
constexpr auto NUMBER_OF_SEPERATING_SPACES = 4;
constexpr auto SEPERATING_SPACES = "    ";
constexpr auto MAX_ROW_LENGTH = 32; // 6 cards (each card two digit) + SEPARATING_SPACES

constexpr auto HIDDEN_STRING = "??";
constexpr auto TAKEN_STRING = "XX";


void DeckDisplayer::Show(const CardAgeType card_age, const std::vector<std::shared_ptr<const Card>>& last_row_in_deck)
{
	std::cout << std::endl;
	switch (card_age) {
		case FIRST_AGE: showFirstAge(last_row_in_deck); break;
		case SECOND_AGE: showSecondAge(last_row_in_deck); break;
		case THIRD_AGE: showThirdAge(last_row_in_deck); break;
		default: throw DECK_NOT_FOUND;
	}
	std::cout << std::endl;
}

void DeckDisplayer::showFirstAge(const std::vector<std::shared_ptr<const Card>>& last_row_in_deck)
{
	printPyramid(last_row_in_deck, NUMBER_OF_ROWS);
}

void DeckDisplayer::showSecondAge(const std::vector<std::shared_ptr<const Card>>& last_row_in_deck)
{
	printInversePyramid(last_row_in_deck, NUMBER_OF_ROWS);
}

void DeckDisplayer::showThirdAge(const std::vector<std::shared_ptr<const Card>>& last_row_in_deck)
{
	std::vector<std::shared_ptr<const Card>> previous_row = printPyramid(last_row_in_deck, 3);
	std::vector<std::shared_ptr<const Card>> middle_row = { previous_row[0]->child_right , previous_row[2]->child_right };
	std::vector<std::shared_ptr<const Card>> next_row = {
		middle_row[0]->child_left, 
		middle_row[0]->child_right, 
		middle_row[1]->child_left, 
		middle_row[1]->child_right };
	
	printThirdAgeMiddleRow(middle_row);
	printInversePyramid(next_row, 3);
}

uint32_t DeckDisplayer::getLength(const std::vector<std::shared_ptr<const Card>>& row)
{
	return (uint32_t(row.size()) * 2) + (uint32_t(row.size() - 1) * NUMBER_OF_SEPERATING_SPACES);
}

std::vector<std::shared_ptr<const Card>> DeckDisplayer::printPyramid(const std::vector<std::shared_ptr<const Card>>& start_row, const uint32_t number_of_rows)
{
	std::vector<std::shared_ptr<const Card>> previous_row = start_row;
	std::vector<std::shared_ptr<const Card>> current_row;

	for (uint32_t row_counter = 1; row_counter < number_of_rows; row_counter++) {
		current_row.resize(0);
		for (uint32_t idx = 0; idx < previous_row.size(); idx++) {
			current_row.push_back(previous_row[idx]->child_left);
		}
		current_row.push_back(previous_row.back()->child_right);

		printRow(previous_row);
		previous_row = current_row;
	}

	printRow(previous_row);
	return previous_row;
}

std::vector<std::shared_ptr<const Card>> DeckDisplayer::printInversePyramid(const std::vector<std::shared_ptr<const Card>>& start_row, const uint32_t number_of_rows)
{
	
	std::vector<std::shared_ptr<const Card>> previous_row = start_row;
	std::vector<std::shared_ptr<const Card>> current_row;

	for (uint32_t row_counter = 1; row_counter < number_of_rows; row_counter++) {
		current_row.resize(0);
		for (uint32_t idx = 0; idx < (previous_row.size() - 1); idx++) {
			current_row.push_back(previous_row[idx]->child_right);
		}

		printRow(previous_row);
		previous_row = current_row;
	}

	printRow(previous_row);
	return previous_row;
}

void DeckDisplayer::printThirdAgeMiddleRow(const std::vector<std::shared_ptr<const Card>>& row)
{
	// Imitate having a third card in the middle
	uint32_t extra_middle_space = 2 + (2 * NUMBER_OF_SEPERATING_SPACES);
	uint32_t length = getLength(row) + extra_middle_space;

	for (uint32_t idx = 0; idx < ((MAX_ROW_LENGTH - length) / 2); idx++) {
		std::cout << " ";
	}

	printCard(row[0]);

	for (uint32_t idx = 0; idx < extra_middle_space; idx++) {
		std::cout << " ";
	}

	printCard(row[1]);

	std::cout << std::endl;
}

void DeckDisplayer::printRow(const std::vector<std::shared_ptr<const Card>>& row)
{
	for (uint32_t idx = 0; idx < ((MAX_ROW_LENGTH - getLength(row)) / 2); idx++) {
		std::cout << " ";
	}
	for (size_t idx = 0; idx < row.size(); idx++) {
		printCard(row[idx]);
	}
	std::cout << std::endl;
}

void DeckDisplayer::printCard(std::shared_ptr<const Card> card)
{
	if ((card->state == CARD_VISIBLE) || (card->state == CARD_VISIBLE_UNAVAILABLE)) {
		if (card->info.ID < 10) {
			std::cout << "0";
		}
		std::cout << card->info.ID << SEPERATING_SPACES;
	}
	else if (card->state == CARD_HIDDEN) {
		std::cout << HIDDEN_STRING << SEPERATING_SPACES;
	}
	else if (card->state == CARD_TAKEN) {
		std::cout << TAKEN_STRING << SEPERATING_SPACES;
	}
	else {
		throw CARD_INVALID_STATE;
	}
}
