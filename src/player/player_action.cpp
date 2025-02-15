#include "player_action.h"


PlayerAction::PlayerAction() :
	card_id(-1),
	wonder_id(-1),
	card(nullptr),
	wonder(nullptr),
	action_type(NO_PLAYER_ACTION)
{}

bool PlayerAction::isFinal() const
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
