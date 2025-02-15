#pragma once

#include "../enums/player_id.h"
#include "../io/wonder_loader.h"
#include "../management/order_manager.h"


class WonderManager {
public:
	WonderManager(const OrderManager& order_manager);
	
	std::vector<std::shared_ptr<const Wonder>> getWonderSelection();
	std::shared_ptr<const Wonder> getWonder(const uint32_t wonder_id) const;
	
	uint32_t getNumberOfBuiltWonders(const PlayerID player_id) const;
	std::vector<std::shared_ptr<const Wonder>> getPlayerWonders(const PlayerID player_id) const;

	bool canBuildWonder() const;
	void registerWonder(const PlayerID player_id, const uint32_t wonder_id);
	void buildWonder(const PlayerID player_id, const uint32_t wonder_id, const uint32_t card_id);

private:
	WonderLoader wonder_loader;
	uint32_t wonder_idx;
	const std::vector<uint32_t>& wonder_IDs;

	uint32_t number_of_wonders_built;
	std::vector<std::vector<std::shared_ptr<const Wonder>>> wonder_views;
	std::vector<std::vector<std::shared_ptr<Wonder>>> player_wonders;
};
