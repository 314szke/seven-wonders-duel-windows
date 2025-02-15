#include "material_bundle.h"


MaterialBundle::MaterialBundle() :
    materials(NUMBER_OF_MATERIALS, 0)
{}

void MaterialBundle::add(const int type)
{
    switch (type) {
        case WOOD: materials[WOOD] += 1; break;
        case CLAY: materials[CLAY] += 1; break;
        case ROCK: materials[ROCK] += 1; break;
        case PAPER: materials[PAPER] += 1; break;
        case GLASS: materials[GLASS] += 1; break;
    }
}

bool MaterialBundle::isEmpty() const
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (materials[idx] > 0) {
            return false;
        }
    }
    return true;
}

uint32_t MaterialBundle::boundedSubtraction(const uint32_t left, const uint32_t right)
{
    if (right > left) {
        return 0;
    }

    return (left - right);
}
