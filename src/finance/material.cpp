#include "material.h"

#include "../enums/player_id.h"


Material::Material() :
    fixed_price(PlayerID::NUMBER_OF_PLAYERS),
    price(PlayerID::NUMBER_OF_PLAYERS),
    produce(PlayerID::NUMBER_OF_PLAYERS)
{
    fixed_price[PlayerID::ENIKO] = false;
    fixed_price[PlayerID::SIMON] = false;

    price[PlayerID::SIMON] = 2;
    price[PlayerID::ENIKO] = 2;

    produce[PlayerID::SIMON] = 0;
    produce[PlayerID::ENIKO] = 0;
}
