#include "deck_displayer.h"

#include <iostream> 

#include "../enums/exception_types.h"


constexpr auto FIRST_AGE_NUMBER_OF_ROWS = 5;
constexpr auto SECOND_AGE_NUMBER_OF_ROWS = 5;

constexpr auto NUMBER_OF_SEPERATING_SPACES = 2;
constexpr auto SEPERATING_SPACES = "  ";
constexpr auto THIRD_AGE_MAX_LENGTH = 14; // 4 cards + SEPARATING_SPACES


void DeckDisplayer::show(const CardAgeType card_age, const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck)
{
	switch (card_age) {
		case FIRST_AGE: showFirstAge(first_row_in_deck, last_row_in_deck); break;
		case SECOND_AGE: showSecondAge(first_row_in_deck, last_row_in_deck); break;
		case THIRD_AGE: showThirdAge(first_row_in_deck, last_row_in_deck); break;
		default: throw DECK_NOT_FOUND;
	}
}

void DeckDisplayer::showFirstAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck)
{
	uint32_t max_length = getEvenLength(first_row_in_deck);
	printPyramid(last_row_in_deck, FIRST_AGE_NUMBER_OF_ROWS, max_length);
}

void DeckDisplayer::showSecondAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck)
{
	uint32_t max_length = getEvenLength(last_row_in_deck);
	printInversePyramid(last_row_in_deck, SECOND_AGE_NUMBER_OF_ROWS, max_length);
}

void DeckDisplayer::showThirdAge(const std::vector<Card*>& first_row_in_deck, const std::vector<Card*>& last_row_in_deck)
{
	std::vector<Card*> previous_row = printPyramid(last_row_in_deck, 3, THIRD_AGE_MAX_LENGTH);
	std::vector<Card*> middle_row = { previous_row[0]->child_right , previous_row[2]->child_right };
	std::vector<Card*> next_row = { 
		middle_row[0]->child_left, 
		middle_row[0]->child_right, 
		middle_row[1]->child_left, 
		middle_row[1]->child_right };
	
	printThirdAgeMiddleRow(middle_row, THIRD_AGE_MAX_LENGTH);
	printInversePyramid(next_row, 3, THIRD_AGE_MAX_LENGTH);
}

uint32_t DeckDisplayer::getLength(const std::vector<Card*>& row)
{
	uint32_t character_counter = 0;

	for (uint32_t idx = 0; idx < row.size(); idx++) {
		character_counter += (1 + NUMBER_OF_SEPERATING_SPACES);

		if ((row[idx]->state == CARD_VISIBLE) || (row[idx]->state == CARD_VISIBLE_UNAVAILABLE)) {
			if ((row[idx]->info.ID + 1) >= 10) {
				character_counter += 1;
			}
		}
	}
	character_counter -= NUMBER_OF_SEPERATING_SPACES;

	return character_counter;
}

uint32_t DeckDisplayer::getEvenLength(const std::vector<Card*>& row)
{
	uint32_t length = getLength(row);

	if (length % 2 == 0) {
		return length;
	}

	// If length is odd, add an extra space to the middle (or two for odd rows)
	uint32_t extra_length = (row.size() % 2 == 1) ? 2 : 1;
	return (length + extra_length);
}

std::vector<Card*> DeckDisplayer::printPyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows, const uint32_t max_length)
{
	std::vector<Card*> previous_row = start_row;
	std::vector<Card*> current_row;

	for (uint32_t row_counter = 1; row_counter < number_of_rows; row_counter++) {
		current_row.resize(0);
		for (uint32_t idx = 0; idx < previous_row.size(); idx++) {
			current_row.push_back(previous_row[idx]->child_left);
		}
		current_row.push_back(previous_row.back()->child_right);

		printRow(previous_row, max_length);
		previous_row = current_row;
	}

	printRow(previous_row, max_length);
	return previous_row;
}

std::vector<Card*> DeckDisplayer::printInversePyramid(const std::vector<Card*>& start_row, const uint32_t number_of_rows, const uint32_t max_length)
{
	std::vector<Card*> previous_row = start_row;
	std::vector<Card*> current_row;

	for (uint32_t row_counter = 1; row_counter < number_of_rows; row_counter++) {
		current_row.resize(0);
		for (uint32_t idx = 0; idx < (previous_row.size() - 1); idx++) {
			current_row.push_back(previous_row[idx]->child_right);
		}

		printRow(previous_row, max_length);
		previous_row = current_row;
	}

	printRow(previous_row, max_length);
	return previous_row;
}

void DeckDisplayer::printThirdAgeMiddleRow(const std::vector<Card*>& row, const uint32_t max_length)
{
	// Imitate having a third card in the middle
	uint32_t length = getLength(row);
	uint32_t extra_middle_space = 1 + (2 * NUMBER_OF_SEPERATING_SPACES);
	uint32_t even_length = getEvenLength(row) + extra_middle_space;

	if (max_length < even_length) {
		throw DISPLAY_ROW_MISMATCH;
	}

	for (uint32_t idx = 0; idx < ((max_length - even_length) / 2); idx++) {
		std::cout << " ";
	}

	if ((row[0]->state == CARD_VISIBLE) || (row[0]->state == CARD_VISIBLE_UNAVAILABLE)) {
		std::cout << (row[0]->info.ID + 1) << SEPERATING_SPACES;
	}
	else if (row[0]->state == CARD_HIDDEN) {
		std::cout << "0" << SEPERATING_SPACES;
	}
	else if (row[0]->state == CARD_TAKEN) {
		std::cout << "X" << SEPERATING_SPACES;
	}
	else {
		throw CARD_INVALID_STATE;
	}

	for (uint32_t idx = 0; idx < extra_middle_space; idx++) {
		std::cout << " ";
	}

	if ((row[1]->state == CARD_VISIBLE) || (row[1]->state == CARD_VISIBLE_UNAVAILABLE)) {
		std::cout << (row[1]->info.ID + 1);
	}
	else if (row[1]->state == CARD_HIDDEN) {
		std::cout << "0";
	}
	else if (row[1]->state == CARD_TAKEN) {
		std::cout << "X";
	}
	else {
		throw CARD_INVALID_STATE;
	}

	std::cout << std::endl;
}

void DeckDisplayer::printRow(const std::vector<Card*>& row, const uint32_t max_length)
{
	uint32_t length = getLength(row);
	uint32_t even_length = getEvenLength(row);

	if (max_length < even_length) {
		throw DISPLAY_ROW_MISMATCH;
	}
	
	for (uint32_t idx = 0; idx < ((max_length - even_length) / 2); idx++) {
		std::cout << " ";
	}

	std::string extra_space = (length == even_length) ? "" : " ";
	size_t middle_index_1 = (row.size() / 2);
	size_t middle_index_2 = (row.size() % 2 == 1) ? (middle_index_1 + 1) : middle_index_1;

	for (size_t idx = 0; idx < row.size(); idx++) {
		if ((idx == middle_index_1) || (idx == middle_index_2)) {
			std::cout << extra_space;
		}

		if ((row[idx]->state == CARD_VISIBLE) || (row[idx]->state == CARD_VISIBLE_UNAVAILABLE)) {
			std::cout << (row[idx]->info.ID + 1) << SEPERATING_SPACES;
		}
		else if (row[idx]->state == CARD_HIDDEN) {
			std::cout << "0" << SEPERATING_SPACES;
		}
		else if (row[idx]->state == CARD_TAKEN) {
			std::cout << "X" << SEPERATING_SPACES;
		}
		else {
			throw CARD_INVALID_STATE;
		}
	}

	std::cout << std::endl;
}
