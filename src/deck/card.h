#pragma once

#include "card_info.h"
#include "card_cost.h"
#include "card_gain.h"


class Card {
public:
    Card(const CardInfo& card_info, const CardCost& card_cost, const CardGain& card_gain);
    
    CardInfo info;
    CardCost cost;
    CardGain gain;

    bool is_visible;
    bool is_taken;

    Card* parent_left;
    Card* parent_right;
};
