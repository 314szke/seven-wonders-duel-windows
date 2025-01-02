#pragma once

#include "../enums/wonder_actions.h"
#include "../finance/material_bundle.h"


class Wonder {
public:
    Wonder();
private:
    uint32_t ID;

    MaterialBundle material_cost;

    uint32_t money;
    uint32_t enemy_money;
    uint32_t victory_point;
    uint32_t military_point;

    WonderAction action;
    MaterialBundle bound_materials;
};
