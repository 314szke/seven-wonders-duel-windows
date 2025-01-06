#pragma once

#include <memory>

#include "../player/player.h"
#include "../game/game.h"


class PlayerDisplayer {
public:
	static void Show(const std::unique_ptr<Player>& player, const Game& game);
};