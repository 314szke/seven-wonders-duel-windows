#pragma once

#include "../enums/chain_symbols.h"
#include "../enums/guild_actions.h"
#include "../enums/player_dependent_actions.h"
#include "../enums/science_symbols.h"
#include "../finance/material_bundle.h"


class CardGain {
public:
    CardGain(
        const uint32_t card_money,
        const uint32_t card_victory_point,
        const uint32_t card_military_point,
//
        const int card_chain_symbol,
        const int card_science_symbol,
//
        const bool card_production_deal,
        const bool card_bounded_materials,
        const MaterialBundle& card_materials,
//
        const int card_action,
        const int card_guild_action);

    uint32_t money;
    uint32_t victory_point;
    uint32_t military_point;

    ChainSymbol chain_symbol;
    ScienceSymbol science_symbol;

    bool production_deal;
    bool bounded_material;
    MaterialBundle materials;

    PlayerDependentAction action;
    GuildAction guild_action;
};

