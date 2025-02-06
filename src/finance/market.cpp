#include "market.h"

#include <limits>

#include "../constants.h"
#include "../enums/player_id.h"


Market::Market() :
    produce(NUMBER_OF_PLAYERS),
    hybrid_produce(NUMBER_OF_PLAYERS),
    price(NUMBER_OF_PLAYERS),
    deals(NUMBER_OF_PLAYERS)
{
    price[SIMON].resize(NUMBER_OF_MATERIALS, 0);
    price[ENIKO].resize(NUMBER_OF_MATERIALS, 0);

    deals[SIMON].resize(NUMBER_OF_MATERIALS, false);
    deals[ENIKO].resize(NUMBER_OF_MATERIALS, false);
}

uint32_t Market::getPurchasePrice(const PlayerID player_id, const MaterialBundle& bundle) const
{
    MaterialBundle remaining = bundle;
    remaining -= produce[player_id];
    remaining -= getBestHybridProduce(player_id, bundle);
    return getBundlePrice(player_id, remaining);
}

void Market::productionChange(const PlayerID player_id, const MaterialBundle& bundle)
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        produce[player_id].materials[idx] += bundle.materials[idx];
        recalculatePriceFor(SIMON, idx);
        recalculatePriceFor(ENIKO, idx);
    }
}

void Market::productionDeal(const PlayerID player_id, const MaterialBundle& bundle)
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (bundle.materials[idx]) {
            deals[player_id][idx] = true;
            price[player_id][idx] = 1;
        }
    }
}

uint32_t Market::getProducedAmount(const PlayerID player_id, const MaterialType type) const
{
    return produce[player_id].materials[type];
}

MaterialBundle Market::getBestHybridProduce(const PlayerID player_id, const MaterialBundle& bundle) const
{
    uint32_t best_save = std::numeric_limits<uint32_t>::infinity();
    MaterialBundle best_solution;

    std::vector<uint32_t> material_per_hybrid_produce(hybrid_produce[player_id].size(), 0);
    do {
        MaterialBundle current_solution;
        for (uint32_t idx = 0; idx < material_per_hybrid_produce.size(); idx++) {
            current_solution.add(material_per_hybrid_produce[idx]);
        }

        uint32_t current_save = std::numeric_limits<uint32_t>::infinity();
        if (isValid(current_solution, bundle)) {
            current_save = getBundlePrice(player_id, current_solution);
        }
        
        if (current_save < best_save) {
            best_save = current_save;
            best_solution = current_solution;
        }
    } while (getNextPermutation(player_id, material_per_hybrid_produce));

    return best_solution;
}

bool Market::getNextPermutation(const PlayerID player_id, std::vector<uint32_t>& material_per_hybrid_produce) const
{
    for (int idx = 0; idx < material_per_hybrid_produce.size(); idx++) {
        material_per_hybrid_produce[idx]++;

        if (material_per_hybrid_produce[idx] >= NUMBER_OF_MATERIALS) {
            material_per_hybrid_produce[idx] = 0;
        } else {
            if (hybrid_produce[player_id][idx].materials[material_per_hybrid_produce[idx]] == 1) {
                return true;
            } else {
                idx--; // if material is not produced, increase on current idx
            }
        }
    }
    return false;
}

bool Market::isValid(const MaterialBundle& produce, const MaterialBundle& requirement) const
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (produce.materials[idx] > requirement.materials[idx]) {
            return false;
        }
    }
    return true;
}

uint32_t Market::getBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const
{
    uint32_t boundle_price = 0;
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        boundle_price += price[player_id][idx] * bundle.materials[idx];
    }
    return boundle_price;
}

void Market::recalculatePriceFor(const PlayerID player_id, const uint32_t material_idx)
{
    if (deals[player_id][material_idx]) {
        return;
    }

    uint32_t other_id = (player_id == 0) ? 1 : 0;
    int production_difference = produce[other_id].materials[material_idx];
    production_difference -= produce[player_id].materials[material_idx];

    if (production_difference < 0) {
        production_difference = 0;
    }

    price[player_id][material_idx] = 2 + production_difference;
}
