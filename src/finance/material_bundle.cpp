#include "material_bundle.h"


MaterialBundle::MaterialBundle() :
    empty(true),
    wood(0),
    clay(0),
    rock(0),
    paper(0),
    glass(0)
{}

void MaterialBundle::add(const int type, const uint32_t amount)
{
    empty = false;
    switch (type) {
        case WOOD : wood += amount; break;
        case CLAY : clay += amount; break;
        case ROCK : rock += amount; break;
        case PAPER : paper += amount; break;
        case GLASS : glass += amount; break;
    }
}
