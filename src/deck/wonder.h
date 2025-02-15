
#pragma once

#include "../enums/player_id.h"
#include "../enums/wonder_actions.h"
#include "../finance/material_bundle.h"


class Wonder {
public:
    Wonder(const uint32_t wonder_id);
    bool isBuilt() const;

    uint32_t ID;
    PlayerID player_id;
    int build_card_id;

    MaterialBundle material_cost;

    uint32_t money;
    uint32_t enemy_money;
    uint32_t victory_point;
    uint32_t military_point;

    WonderAction action;
    MaterialBundle hybrid_materials;
};
