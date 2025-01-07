#include "market.h"

#include "../enums/material_types.h"


uint32_t Market::getMaterialBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const
{
    MaterialBundle remaining_materials = extractMissingMaterials(player_id, bundle);
    
    uint32_t price = 0;
    price += wood.price[player_id] * remaining_materials.wood;
    price += clay.price[player_id] * remaining_materials.clay;
    price += rock.price[player_id] * remaining_materials.rock;

    price += paper.price[player_id] * remaining_materials.paper;
    price += glass.price[player_id] * remaining_materials.glass;

    return price;
}

void Market::productionChange(const PlayerID player_id, const MaterialBundle& bundle)
{
    productionChange(wood, player_id, bundle.wood);
    productionChange(clay, player_id, bundle.clay);
    productionChange(rock, player_id, bundle.rock);
    productionChange(paper, player_id, bundle.paper);
    productionChange(glass, player_id, bundle.glass);
}

void Market::productionDeal(const PlayerID player_id, const MaterialBundle& bundle)
{
    productionDeal(wood, player_id, bundle.wood);
    productionDeal(clay, player_id, bundle.clay);
    productionDeal(rock, player_id, bundle.rock);
    productionDeal(paper, player_id, bundle.paper);
    productionDeal(glass, player_id, bundle.glass);
}

MaterialBundle Market::extractMissingMaterials(const PlayerID player_id, const MaterialBundle& bundle) const
{
    MaterialBundle remaining_materials = bundle;
    
    remaining_materials.wood = getRemainingValue(bundle.wood, wood.produce[player_id]);
    remaining_materials.clay = getRemainingValue(bundle.clay, clay.produce[player_id]);
    remaining_materials.rock = getRemainingValue(bundle.rock, rock.produce[player_id]);

    remaining_materials.paper = getRemainingValue(bundle.paper, paper.produce[player_id]);
    remaining_materials.glass = getRemainingValue(bundle.glass, glass.produce[player_id]);

    return remaining_materials;
}

uint32_t Market::getRemainingValue(const uint32_t left_value, const uint32_t right_value) const
{
    if (left_value < right_value) {
        return 0;
    }

    return (left_value - right_value);
}

void Market::productionChange(Material& material, const PlayerID player_id, int amount)
{
    if (amount == 0) {
        return;
    }

    material.produce[player_id] += amount;
    recalculatePriceFor(SIMON, material);
    recalculatePriceFor(ENIKO, material);
}

void Market::productionDeal(Material& material, const PlayerID player_id, bool active)
{
    if (! active) {
        return;
    }

    material.fixed_price[player_id] = true;
    material.price[player_id] = 1;
}

void Market::recalculatePriceFor(const PlayerID player_id, Material& material)
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
