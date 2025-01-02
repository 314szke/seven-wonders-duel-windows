#include "material.h"

#include "../enums/player_id.h"


Material::Material() :
    fixed_price(NUMBER_OF_PLAYERS),
    price(NUMBER_OF_PLAYERS),
    produce(NUMBER_OF_PLAYERS)
{
    fixed_price[ENIKO] = false;
    fixed_price[SIMON] = false;

    price[SIMON] = 2;
    price[ENIKO] = 2;

    produce[SIMON] = 0;
    produce[ENIKO] = 0;
}
