#pragma once

#include "player.h"


class ConsolPlayer : public Player {
public:
	ConsolPlayer(const PlayerID player_id, const std::string player_name);

	PlayerAction play(const Game& game) override;
};
