#pragma once

#include "card_info.h"
#include "card_cost.h"
#include "card_gain.h"
#include "../enums/card_states.h"


class Card {
public:
    Card(const CardInfo& card_info, const CardCost& card_cost, const CardGain& card_gain);
    
    const CardInfo info;
    const CardCost cost;
    const CardGain gain;

    CardState state;

    Card* parent_left;
    Card* parent_right;

    Card* child_left;
    Card* child_right;
};
