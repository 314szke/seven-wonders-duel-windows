#pragma once

#include <stdint.h>

#include "material.h"
#include "material_bundle.h"
#include "../enums/player_id.h"


class Market {
public:
    uint32_t getMaterialBundlePrice(const PlayerID player_id, const MaterialBundle& bundle) const;

    void productionChange(const PlayerID player_id, const MaterialBundle& bundle);
    void productionDeal(const PlayerID player_id, const MaterialBundle& bundle);

private:
    MaterialBundle extractMissingMaterials(const PlayerID player_id, const MaterialBundle& bundle) const;
    uint32_t getRemainingValue(const uint32_t left_value, const uint32_t right_value) const;
    void productionChange(Material& material, const PlayerID player_id, int amount);
    void productionDeal(Material& material, const PlayerID player_id, bool active);
    void recalculatePriceFor(const PlayerID player_id, Material& material);

    Material wood;
    Material clay;
    Material rock;

    Material paper;
    Material glass;
};

