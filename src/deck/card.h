#pragma once

#include "../enums/card_age_types.h"
#include "../enums/card_colors.h"
#include "../enums/chain_symbols.h"
#include "../enums/guild_actions.h"
#include "../enums/player_dependent_actions.h"
#include "../enums/science_symbols.h"
#include "../finance/material_bundle.h"


class Card {
public:
    Card();
private:
    uint32_t ID;

    CardAgeType age;
    CardColor type;

    uint32_t cost_money;
    MaterialBundle cost_material;
    ChainSymbol cost_symbol;

    uint32_t gain_money;
    uint32_t gain_victory_point;
    uint32_t gain_military_point;

    bool gain_production_deal;
    bool gain_bounded_material;
    MaterialBundle gain_material;

    ChainSymbol gain_chain_symbol;
    ScienceSymbol gain_science_symbol;

    PlayerDependentAction gain_action;
    GuildAction gain_guild_action;
};
