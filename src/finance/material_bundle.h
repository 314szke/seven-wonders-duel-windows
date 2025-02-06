#pragma once

#include <stdint.h>
#include <vector>

#include "../enums/material_types.h"


class MaterialBundle {
public:
    MaterialBundle();

    void add(const int material_type);

    MaterialBundle& operator+=(const MaterialBundle& other_bundle)
    {                         
        this->materials[WOOD] += other_bundle.materials[WOOD];
        this->materials[CLAY] += other_bundle.materials[CLAY];
        this->materials[ROCK] += other_bundle.materials[ROCK];

        this->materials[PAPER] += other_bundle.materials[PAPER];
        this->materials[GLASS] += other_bundle.materials[GLASS];
        return *this;
    }    
    
    MaterialBundle& operator-=(const MaterialBundle& other_bundle)
    {                         
        this->materials[WOOD] = boundedSubtraction(this->materials[WOOD], other_bundle.materials[WOOD]);
        this->materials[CLAY] = boundedSubtraction(this->materials[CLAY], other_bundle.materials[CLAY]);
        this->materials[ROCK] = boundedSubtraction(this->materials[ROCK], other_bundle.materials[ROCK]);

        this->materials[PAPER] = boundedSubtraction(this->materials[PAPER], other_bundle.materials[PAPER]);
        this->materials[GLASS] = boundedSubtraction(this->materials[GLASS], other_bundle.materials[GLASS]);
        return *this;
    }

    std::vector<uint32_t> materials;

private:

    uint32_t boundedSubtraction(const uint32_t left, const uint32_t right);
};
