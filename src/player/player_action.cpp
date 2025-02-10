#include "player_action.h"


PlayerAction::PlayerAction() :
	card_id(-1),
	card(nullptr),
	action_type(NO_PLAYER_ACTION)
{}

bool PlayerAction::isNotDone() const
{
	return (action_type == NO_PLAYER_ACTION || action_type == INFO);
}
