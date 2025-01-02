#include "material_bundle.h"


MaterialBundle::MaterialBundle() :
    empty(true),
    wood(0),
    clay(0),
    rock(0),
    paper(0),
    glass(0)
{}

void MaterialBundle::add(const MaterialType type, const uint32_t amount)
{
    empty = false;
    switch(type) {
        case MaterialType::WOOD : wood += amount; break;
        case MaterialType::CLAY : clay += amount; break;
        case MaterialType::ROCK : rock += amount; break;
        case MaterialType::PAPER : paper += amount; break;
        case MaterialType::GLASS : glass += amount; break;
    }
}
