#pragma once

#include <string>

#include "../enums/player_id.h"
#include "../enums/player_types.h"
#include "../player/player_action.h"


class ConsolInput {
public:
	static PlayerType ReadPlayerOption(const PlayerID player_id);
	static std::string ReadPlayerName(const PlayerID player_id);
	static PlayerAction ReadPlayerAction(const std::string& player_name);
};
