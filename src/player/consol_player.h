#pragma once

#include "player.h"


class ConsolPlayer : public Player {
public:
	ConsolPlayer(const PlayerID player_id, const std::string player_name);

	uint32_t play(const std::vector<Card*>& visible_cards) override;
};
