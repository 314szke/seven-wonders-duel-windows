#pragma once

#include <stdint.h>
#include <vector>

#include "material_bundle.h"
#include "../enums/material_types.h"
#include "../enums/player_id.h"


class Market {
public:
    Market();

    uint32_t getMaterialBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const;

    void productionChange(const PlayerID player_id, const MaterialBundle& bundle);
    void productionDeal(const PlayerID player_id, const MaterialBundle& bundle);
    uint32_t getProducedAmount(const PlayerID player_id, const MaterialType type) const;

private:
    MaterialBundle extractMissingMaterials(const PlayerID player_id, const MaterialBundle& bundle) const;
    MaterialBundle getBestHybridProduce(const PlayerID player_id, const MaterialBundle& bundle);
    void recalculatePriceFor(const PlayerID player_id, const uint32_t material_idx);

    std::vector<MaterialBundle> produce;
    std::vector<std::vector<MaterialBundle>> hybrid_produce;
    std::vector<std::vector<uint32_t>> price;
    std::vector<std::vector<bool>> deals;
};

