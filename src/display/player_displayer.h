#pragma once

#include <memory>

#include "../player/player.h"
#include "../game/game.h"


class PlayerDisplayer {
public:
	PlayerDisplayer(Game& game_ref);

	void show(const std::unique_ptr<Player>& player);

private:
	Game& game;
};