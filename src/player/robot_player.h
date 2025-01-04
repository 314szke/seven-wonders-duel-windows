#pragma once

#include "player.h"

#include "../deck/card.h"


class RobotPlayer : public Player {
public:
	RobotPlayer(const PlayerID player_id, const std::string player_name);

	uint32_t play(const std::vector<Card*>& visible_cards) override;
};
