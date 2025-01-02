#pragma once

#include <vector>


class Material {
public:
    Material();

    std::vector<bool> fixed_price;
    std::vector<uint32_t> price;
    std::vector<uint32_t> produce;
};

