#pragma once

#include "player.h"


class ConsolPlayer : public Player {
public:
	ConsolPlayer(const PlayerID player_id, const std::string player_name);

	PlayerAction play(const Game& game) override;
	uint32_t selectWonder(const std::vector<std::shared_ptr<const Wonder>>& wonders);
	std::shared_ptr<const Card> chooseCard(const std::vector<std::shared_ptr<const Card>>& cards);
	std::shared_ptr<const Card> chooseCardToDiscard(const std::vector<std::shared_ptr<const Card>>& cards);

private:
	bool processAction(const Game& game, PlayerAction& action);
	bool getActionCard(const Game& game, PlayerAction& action);
	bool getActionWonder(const Game& game, PlayerAction& action);

	std::shared_ptr<const Card> chooseCard(const std::vector<std::shared_ptr<const Card>>& cards, std::string message);
};
