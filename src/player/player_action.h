#pragma once

#include <stdint.h>

#include "../enums/player_action_type.h"
#include "../deck/card.h"
#include "../deck/wonder.h"


class PlayerAction {
public:
	PlayerAction();
	
	bool isFinal() const;

	int card_id;
	int wonder_id;
	std::shared_ptr<const Card> card;
	std::shared_ptr<const Wonder> wonder;
	PlayerActionType action_type;
};