#include "wonder_manager.h"

#include "../constants.h"


WonderManager::WonderManager(const OrderManager& order_manager) :
	wonder_idx(0),
	wonder_IDs(order_manager.getWonderIDs()),
	number_of_wonders_built(0),
	wonder_views(NUMBER_OF_PLAYERS),
	player_wonders(NUMBER_OF_PLAYERS)
{}

std::vector<std::shared_ptr<const Wonder>> WonderManager::getWonderSelection()
{
	std::vector<std::shared_ptr<const Wonder>> wonders;
	uint32_t end_idx = (wonder_idx + 4);
	for (; wonder_idx < end_idx; wonder_idx++) {
		wonders.push_back(wonder_loader.getWonder(wonder_IDs[wonder_idx]));
	}
	return wonders;
}

std::shared_ptr<const Wonder> WonderManager::getWonder(const uint32_t wonder_id) const
{
	return wonder_loader.getWonder(wonder_id);
}

uint32_t WonderManager::getNumberOfBuiltWonders(const PlayerID player_id) const
{
	uint32_t counter = 0;
	for (std::shared_ptr<Wonder> wonder : player_wonders[player_id]) {
		if (wonder->isBuilt()) {
			counter++;
		}
	}
	return counter;
}

std::vector<std::shared_ptr<const Wonder>> WonderManager::getPlayerWonders(const PlayerID player_id) const
{
	return wonder_views[player_id];
}

bool WonderManager::canBuildWonder() const
{
	if (number_of_wonders_built < MAX_NUMBER_OF_BUILT_WONDERS) {
		return true;
	}
	return false;
}

void WonderManager::registerWonder(const PlayerID player_id, const uint32_t wonder_id)
{
	std::shared_ptr<Wonder> wonder = wonder_loader.getWonder(wonder_id);
	wonder->player_id = player_id;

	wonder_views[player_id].push_back(wonder);
	player_wonders[player_id].push_back(wonder);
}

void WonderManager::buildWonder(const PlayerID player_id, const uint32_t wonder_id, const uint32_t card_id)
{
	if (number_of_wonders_built >= MAX_NUMBER_OF_BUILT_WONDERS) {
		return;
	}

	for (std::shared_ptr<Wonder> wonder : player_wonders[player_id]) {
		if (wonder->ID == wonder_id) {
			wonder->build_card_id = card_id;
		}
	}
}
