#pragma once

#include <random>

#include "../deck/card.h"
#include "../player/player.h"


class RobotPlayer : public Player {
public:
	RobotPlayer(const PlayerID player_id, const std::string player_name);

	PlayerAction play(const Game& game) override;

private:
	std::random_device rd;
	std::mt19937 engine;
};
