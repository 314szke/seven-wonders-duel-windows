#include "card.h"


Card::Card(const CardInfo& card_info, const CardCost& card_cost, const CardGain& card_gain) :
	info(card_info),
	cost(card_cost),
	gain(card_gain),
//
	state(CARD_UNUSED)
{}
