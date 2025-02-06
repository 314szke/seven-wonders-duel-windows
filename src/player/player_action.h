#pragma once

#include <stdint.h>

#include "../enums/player_action_type.h"
#include "../deck/card.h"


class PlayerAction {
public:
	PlayerAction();

	int card_id;
	Card* card;
	PlayerActionType action_type;
};