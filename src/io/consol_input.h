#pragma once

#include <string>

#include "../enums/player_id.h"
#include "../enums/player_types.h"


class ConsolInput {
public:
	static PlayerType readPlayerOption(const PlayerID player_id);
	static std::string readPlayerName(const PlayerID player_id);
	static uint32_t readCardID();
};
