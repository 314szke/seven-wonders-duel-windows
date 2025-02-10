#pragma once

#include <memory>

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

    std::shared_ptr<Card> parent_left;
    std::shared_ptr<Card> parent_right;

    std::shared_ptr<Card> child_left;
    std::shared_ptr<Card> child_right;
};
