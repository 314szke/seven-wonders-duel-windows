#include "card_loader.h"

#include <iostream>
#include <regex>

#include "../enums/exception_types.h"
#include "../enums/card_options.h"
#include "../constants.h"


static const std::string CARD_FILE = "../../data/cards.csv";
static const std::regex CARD_DETAILS_PATTERN("([0-9][0-9]?);([1-3]);([0-6]);([0-8]);(-|[0-4]|(?:(?:[0-4],)+[0-4]));(-|[0-9][0-9]?);(0|4|6);([0-7]);([0-3]);(0|1);(0|1);(-|[0-4]|(?:(?:[0-4],)+[0-4]));(-|[0-9][0-9]?);(-|[0-5]);(-|[0-4]);(-|[0-6])\\r?\\n?");


CardLoader::CardLoader()
{
	f_in.open(CARD_FILE);

	// Skip the header in the CSV file
	readLine(); 
	
	std::smatch match;
	for (uint32_t id = 0; id < TOTAL_NUMBER_OF_CARDS; id++) {
		readLine();
		
		if (std::regex_match(line, match, CARD_DETAILS_PATTERN)) {
			parseCardDetails(id, match);
		} else {
			throw FILE_READ_CARD_REGEX_FAIL;
		}
	}
}

const Card& CardLoader::getCard(const uint32_t card_id) const
{
	if (card_id > cards.size()) {
		throw CARD_INDEX_OUT_OF_BOUND;
	}
	
	return cards[card_id];
}

void CardLoader::parseCardDetails(const uint32_t card_id, const std::smatch& match)
{
	CardInfo info(
		card_id,
		parseNumber<uint32_t>(match[AGE]),
		parseNumber<uint32_t>(match[COLOR]));

	CardCost cost(
		parseNumber<uint32_t>(match[COST_MONEY]),
		parseMaterialBundle(match[COST_MATERIALS]),
		parseNumber<int>(match[COST_SYMBOL]));

	CardGain gain(
		parseNumber<uint32_t>(match[GAIN_MONEY]),
		parseNumber<uint32_t>(match[GAIN_VICTORY_POINT]),
		parseNumber<uint32_t>(match[GAIN_MILITARY_POINT]),
//
		parseNumber<int>(match[GAIN_CHAIN_SYMBOL]),
		parseNumber<int>(match[GAIN_SCIENCE_SYMBOL]),
//
		parseNumber<bool>(match[GAIN_PRODUCTION_DEAL]),
		parseNumber<bool>(match[GAIN_BOUNDED_MATERIAL]),
		parseMaterialBundle(match[GAIN_MATERIALS]),
//
		parseNumber<int>(match[GAIN_ACTION]),
		parseNumber<int>(match[GAIN_GUILD_ACTION]));

	cards.push_back(Card(info, cost, gain));
}
