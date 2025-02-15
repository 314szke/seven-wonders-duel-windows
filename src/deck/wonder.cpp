#include "wonder.h"


Wonder::Wonder(const uint32_t wonder_id) :
	ID(wonder_id),
	player_id(NO_PLAYER),
	build_card_id(-1),
	money(0),
	enemy_money(0),
	victory_point(0),
	military_point(0),
	action(NO_WONDER_ACTION)
{}

bool Wonder::isBuilt() const
{
	return (build_card_id != -1);
}