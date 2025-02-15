#pragma once

#include <stdint.h>
#include <vector>

#include "material_bundle.h"
#include "../enums/material_types.h"
#include "../enums/player_id.h"


class PlayerDisplayer;


class Market {
public:
    friend class PlayerDisplayer;

    Market();

    uint32_t getMaterialPrice(const PlayerID player_id, const MaterialBundle& bundle) const;
    
    void productionIncrease(const PlayerID player_id, const MaterialBundle& bundle);
    void productionDecrease(const PlayerID player_id, const MaterialBundle& bundle);

    void productionDeal(const PlayerID player_id, const MaterialBundle& bundle);
    void hybridProduction(const PlayerID player_id, const MaterialBundle& bundle);

private:
    MaterialBundle getBestHybridProduce(const PlayerID player_id, const MaterialBundle& bundle) const;
    bool getNextPermutation(const PlayerID player_id, std::vector<uint32_t>& material_per_hybrid_produce) const;
    bool isValid(const MaterialBundle& produce, const MaterialBundle& requirement) const;

    uint32_t getBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const;
    void recalculatePriceFor(const PlayerID player_id, const uint32_t material_idx);

    std::vector<MaterialBundle> produce;
    std::vector<std::vector<MaterialBundle>> hybrid_produce;
    std::vector<std::vector<uint32_t>> price;
    std::vector<std::vector<bool>> deals;
};

