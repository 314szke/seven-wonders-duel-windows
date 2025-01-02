#include "market.h"

#include "../enums/material_types.h"
#include "../enums/player_id.h"


uint32_t Market::getMaterialBundlePrice(const uint32_t player_id, MaterialBundle& bundle) const
{
    uint32_t price = 0;
    price += wood.price[player_id] * bundle.wood;
    price += clay.price[player_id] * bundle.clay;
    price += rock.price[player_id] * bundle.rock;

    price += paper.price[player_id] * bundle.paper;
    price += glass.price[player_id] * bundle.glass;

    return price;
}

void Market::productionChange(const MaterialType material_type, const uint32_t player_id, int amount)
{
    switch (material_type) {
    case MaterialType::WOOD: productionChange(wood, player_id, amount); break;
    case MaterialType::CLAY: productionChange(clay, player_id, amount); break;
    case MaterialType::ROCK: productionChange(rock, player_id, amount); break;
    case MaterialType::PAPER: productionChange(paper, player_id, amount); break;
    case MaterialType::GLASS: productionChange(glass, player_id, amount); break;
    }
}

void Market::productionDeal(const MaterialType material_type, const uint32_t player_id)
{
    switch (material_type) {
    case MaterialType::WOOD: productionDeal(wood, player_id); break;
    case MaterialType::CLAY: productionDeal(clay, player_id); break;
    case MaterialType::ROCK: productionDeal(rock, player_id); break;
    case MaterialType::PAPER: productionDeal(paper, player_id); break;
    case MaterialType::GLASS: productionDeal(glass, player_id); break;
    }
}

void Market::productionChange(Material& material, const uint32_t player_id, int amount)
{
    material.produce[player_id] += amount;
    recalculatePriceFor(PlayerID::SIMON, material);
    recalculatePriceFor(PlayerID::ENIKO, material);
}

void Market::productionDeal(Material& material, const uint32_t player_id)
{
    material.fixed_price[player_id] = true;
    material.price[player_id] = 1;
}

void Market::recalculatePriceFor(const uint32_t player_id, Material& material)
{
    if (material.fixed_price[player_id]) {
        return;
    }

    uint32_t other_player_id = (player_id == 0) ? 1 : 0;
    int production_difference = material.produce[other_player_id] - material.produce[player_id];
    if (production_difference < 0) {
        production_difference = 0;
    }

    material.price[player_id] = 2 + production_difference;
}
