#pragma once

#include <stdint.h>

#include "../enums/player_action_type.h"
#include "../deck/card.h"


class PlayerAction {
public:
	PlayerAction();
	
	bool isDone() const;

	int card_id;
	std::shared_ptr<const Card> card;
	PlayerActionType action_type;
};