#pragma once

#include <stdint.h>
#include <vector>


class MaterialBundle {
public:
    MaterialBundle();

    void add(const int material_type);

    std::vector<uint32_t> materials;
};
