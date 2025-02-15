#include "card_loader.h"

#include <filesystem>
#include <regex>

#include "../enums/exception_types.h"
#include "../enums/card_options.h"
#include "../constants.h"


static const std::filesystem::path CARD_FILE = "\\data\\cards.csv";
static const std::regex CARD_DETAILS_PATTERN("([0-9][0-9]?);([1-3]);([0-6]);([0-8]);(-|[0-4]|(?:(?:[0-4],)+[0-4]));(-|[0-9][0-9]?);(0|4|6);([0-7]);([0-3]);(0|1);(0|1);(-|[0-4]|(?:(?:[0-4],)+[0-4]));(-|[0-9][0-9]?);(-|[0-5]);(-|[0-4]);(-|[0-6])\\r?\\n?");


CardLoader::CardLoader()
{
	std::filesystem::path card_file_path = std::filesystem::current_path();
	card_file_path += CARD_FILE;
	f_in.open(card_file_path);
	if (!f_in.is_open()) {
		throw FILE_NOT_FOUND;
	}

	// Skip the header in the CSV file
	readLine(); 
	
	std::smatch match;
	for (uint32_t id = 0; id < TOTAL_NUMBER_OF_CARDS; id++) {
		readLine();
		
		if (std::regex_match(line, match, CARD_DETAILS_PATTERN)) {
			parseCard(id, match);
		} else {
			throw FILE_READ_CARD_REGEX_FAIL;
		}
	}

	f_in.close();
}

std::shared_ptr<const Card> CardLoader::getCard(const uint32_t card_id) const
{
	if (card_id > cards.size()) {
		throw CARD_INDEX_OUT_OF_BOUND;
	}
	
	return std::shared_ptr<const Card>(cards[card_id]);
}

std::shared_ptr<Card> CardLoader::getCard(const uint32_t card_id)
{
	if (card_id > cards.size()) {
		throw CARD_INDEX_OUT_OF_BOUND;
	}

	return cards[card_id];
}

void CardLoader::parseCard(const uint32_t card_id, const std::smatch& match)
{
	CardInfo info(
		card_id,
		parseNumber<uint32_t>(match[AGE], NO_AGE),
		parseNumber<uint32_t>(match[COLOR], NUMBER_OF_CARD_COLORS));

	CardCost cost(
		parseNumber<uint32_t>(match[COST_MONEY], 0),
		parseMaterialBundle(match[COST_MATERIALS]),
		parseNumber<int>(match[COST_SYMBOL], NO_CHAIN));

	CardGain gain(
		parseNumber<uint32_t>(match[GAIN_MONEY], 0),
		parseNumber<uint32_t>(match[GAIN_VICTORY_POINT], 0),
		parseNumber<uint32_t>(match[GAIN_MILITARY_POINT], 0),
//
		parseNumber<int>(match[GAIN_CHAIN_SYMBOL], NO_CHAIN),
		parseNumber<int>(match[GAIN_SCIENCE_SYMBOL], NO_SCIENCE),
//
		parseNumber<bool>(match[GAIN_PRODUCTION_DEAL], false),
		parseNumber<bool>(match[GAIN_HYBRID_MATERIAL], false),
		parseMaterialBundle(match[GAIN_MATERIALS]),
//
		parseNumber<int>(match[GAIN_ACTION], NO_ACTION),
		parseNumber<int>(match[GAIN_GUILD_ACTION], NO_GUILD_ACTION));

	cards.push_back(std::shared_ptr<Card>(new Card(info, cost, gain)));
}
