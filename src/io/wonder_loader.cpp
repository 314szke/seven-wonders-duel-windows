#include "wonder_loader.h"

#include <filesystem>
#include <regex>

#include "../constants.h"
#include "../enums/exception_types.h"
#include "../enums/wonder_options.h"


static const std::filesystem::path WONDER_FILE = "\\data\\wonders.csv";
static const std::regex WONDER_DETAILS_PATTERN("([1-9]?[0-9]);((?:(?:[0-4],)+[0-4]));([1-9]?[0-9]);([03]);([0-9]);([0-2]);(-|[0-4]);(-|(?:(?:[0-4],)+[0-4]))\\r?\\n?");


WonderLoader::WonderLoader()
{
	std::filesystem::path wonder_file_path = std::filesystem::current_path();
	wonder_file_path += WONDER_FILE;
	f_in.open(wonder_file_path);
	if (!f_in.is_open()) {
		throw FILE_NOT_FOUND;
	}

	// Skip the header in the CSV file
	readLine();

	std::smatch match;
	for (uint32_t id = 0; id < TOTAL_NUMBER_OF_WONDERS; id++) {
		readLine();

		if (std::regex_match(line, match, WONDER_DETAILS_PATTERN)) {
			parseWonder(id, match);
		}
		else {
			throw FILE_READ_WONDER_REGEX_FAIL;
		}
	}

	f_in.close();
}

std::shared_ptr<const Wonder> WonderLoader::getWonder(const uint32_t wonder_id) const
{
	if (wonder_id > wonders.size()) {
		throw WONDER_INDEX_OUT_OF_BOUND;
	}

	return std::shared_ptr<const Wonder>(wonders[wonder_id]);
}

std::shared_ptr<Wonder> WonderLoader::getWonder(const uint32_t wonder_id)
{
	if (wonder_id > wonders.size()) {
		throw WONDER_INDEX_OUT_OF_BOUND;
	}

	return wonders[wonder_id];
}

void WonderLoader::parseWonder(const uint32_t wonder_id, const std::smatch& match)
{
	wonders.push_back(std::shared_ptr<Wonder>(new Wonder(wonder_id)));

	wonders.back()->material_cost = parseMaterialBundle(match[WONDER_COST_MATERIALS]);
	wonders.back()->hybrid_materials = parseMaterialBundle(match[WONDER_HYBRID_MATERIAL]);
	
	wonders.back()->money = parseNumber<uint32_t>(match[WONDER_MONEY], 0);
	wonders.back()->enemy_money = parseNumber<uint32_t>(match[WONDER_ENEMY_MONEY], 0);
	wonders.back()->victory_point = parseNumber<uint32_t>(match[WONDER_VICTORY_POINT], 0);
	wonders.back()->military_point = parseNumber<uint32_t>(match[WONDER_MILITARY_POINT], 0);

	switch (parseNumber<int>(match[WONDER_ACTION], NO_WONDER_ACTION)) {
		case BROWN_DISCARD: wonders.back()->action = BROWN_DISCARD; break;
		case GREY_DISCARD: wonders.back()->action = GREY_DISCARD; break;
		case CARD_PICK: wonders.back()->action = CARD_PICK; break;
		case NEW_TURN: wonders.back()->action = NEW_TURN; break;
		case PROGRESS_COIN: wonders.back()->action = PROGRESS_COIN; break;
	}
}
