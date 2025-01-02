#pragma once

#include <stdint.h>

#include "../enums/material_types.h"


class MaterialBundle {
public:
    MaterialBundle();

    void add(const MaterialType type, const uint32_t amount);

    bool empty;

    uint32_t wood;
    uint32_t clay;
    uint32_t rock;

    uint32_t paper;
    uint32_t glass;
};
