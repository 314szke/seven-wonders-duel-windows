#pragma once

#include <vector>


enum PlayerType {
	CONSOL_PLAYER = 0,
	ROBOT_PLAYER = 1
};


static const std::vector<std::string> PLAYER_TYPE_STRINGS = { "0 >> Consol Player", "1 >> Robot Player"};