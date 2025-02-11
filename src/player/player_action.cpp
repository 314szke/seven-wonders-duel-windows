#include "player_action.h"


PlayerAction::PlayerAction() :
	card_id(-1),
	card(nullptr),
	action_type(NO_PLAYER_ACTION)
{}

bool PlayerAction::isDone() const
{
	if (action_type == TAKE) {
		return true;
	}
	if (action_type == DISCARD) {
		return true;
	}
	if (action_type == BUILD) {
		return true;
	}
	return false;
}
