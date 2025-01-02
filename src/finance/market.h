#pragma once

#include <stdint.h>

#include "material.h"
#include "material_bundle.h"
#include "../enums/player_id.h"


#define MATERIAL_NUMBER 5


class Market {
public:
    uint32_t getMaterialBundlePrice(const PlayerID player_id, MaterialBundle& bundle) const;

    void productionChange(const MaterialType material_type, const PlayerID player_id, int amount);
    void productionDeal(const MaterialType material_type, const PlayerID player_id);

private:
    void productionChange(Material& material, const PlayerID player_id, int amount);
    void productionDeal(Material& material, const PlayerID player_id);
    void recalculatePriceFor(const PlayerID player_id, Material& material);

    Material wood;
    Material clay;
    Material rock;

    Material paper;
    Material glass;
};

