#pragma once

#include <stdint.h>

#include "material.h"
#include "material_bundle.h"


#define MATERIAL_NUMBER 5


class Market {
public:
    uint32_t getMaterialBundlePrice(const uint32_t player_id, MaterialBundle& bundle) const;

    void productionChange(const MaterialType material_type, const uint32_t player_id, int amount);
    void productionDeal(const MaterialType material_type, const uint32_t player_id);

private:
    void productionChange(Material& material, const uint32_t player_id, int amount);
    void productionDeal(Material& material, const uint32_t player_id);
    void recalculatePriceFor(const uint32_t player_id, Material& material);

    Material wood;
    Material clay;
    Material rock;

    Material paper;
    Material glass;
};

