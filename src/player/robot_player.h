#pragma once

#include <random>

#include "../deck/card.h"
#include "../player/player.h"


class RobotPlayer : public Player {
public:
	RobotPlayer(const PlayerID player_id, const std::string player_name);

	PlayerAction play(const Game& game) override;
	uint32_t selectWonder(const std::vector<std::shared_ptr<const Wonder>>& wonders);
	std::shared_ptr<const Card> chooseCard(const std::vector<std::shared_ptr<const Card>>& cards);
	std::shared_ptr<const Card> chooseCardToDiscard(const std::vector<std::shared_ptr<const Card>>& cards);

private:
	std::random_device rd;
	std::mt19937 engine;
};
