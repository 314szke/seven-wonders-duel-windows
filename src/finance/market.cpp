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

uint32_t Market::getMaterialBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const
{
    MaterialBundle remaining = extractMissingMaterials(player_id, bundle);
    
    uint32_t boundle_price = 0;
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        boundle_price += price[player_id][idx] * remaining.materials[idx];
    }

    return boundle_price;
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

MaterialBundle Market::extractMissingMaterials(const PlayerID player_id, const MaterialBundle& bundle) const
{
    MaterialBundle remaining = bundle;
    
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (remaining.materials[idx] > produce[player_id].materials[idx]) {
            remaining.materials[idx] -= produce[player_id].materials[idx];
        } else {
            remaining.materials[idx] = 0;
        }
    }
    
    return remaining;
}

MaterialBundle Market::getBestHybridProduce(const PlayerID player_id, const MaterialBundle& bundle)
{
    MaterialBundle remaining;
    if (hybrid_produce[player_id].empty()) {
        return remaining;
    }
    
    uint32_t best_save = std::numeric_limits<uint32_t>::infinity();
    uint32_t current_save = 0;
    std::vector<uint32_t> best_solution;
    std::vector<uint32_t> current_solution(hybrid_produce[player_id].size(), 0);

    bool done = false;
    do {
        current_save = 0;
        for (uint32_t idx = 0; idx < current_solution.size(); idx++) {
            current_save += price[player_id][current_solution[idx]];
        }
        if (current_save < best_save) {
            best_save = current_save;
            best_solution = current_solution;
        }

        done = true;
        for (int idx = (hybrid_produce[player_id].size() - 1); idx >= 0; idx--) {
            if (++current_solution[idx] >= NUMBER_OF_MATERIALS) {
                current_solution[idx] = 0;
            } else {
                if (hybrid_produce[player_id][idx].materials[current_solution[idx]] == 1) {
                    done = false;
                    break;
                }
            }
        }
    } while (! done);

    for (uint32_t idx = 0; idx < best_solution.size(); idx++) {
        remaining.materials[best_solution[idx]]--;
    }
    return remaining;
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
