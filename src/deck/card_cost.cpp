#include "card_cost.h"

#include "../enums/chain_symbols.h"


CardCost::CardCost(const uint32_t money_cost, const MaterialBundle& material_cost, const int symbol_cost) :
	money(money_cost),
    materials(material_cost)
{
    switch (symbol_cost) {
        case VASE: symbol = VASE; break;
        case SWORD: symbol = SWORD; break;
        case TOWER: symbol = TOWER; break;
        case HORSESHOE: symbol = HORSESHOE; break;
        case BOOK: symbol = BOOK; break;
        case GEAR: symbol = GEAR; break;
        case MOON: symbol = MOON; break;
        case WATER: symbol = WATER; break;
        case MASK: symbol = MASK; break;
        case BARREL: symbol = BARREL; break;
        case TARGET: symbol = TARGET; break;
        case HELMET: symbol = HELMET; break;
        case TEAPOT: symbol = TEAPOT; break;
        case HARP: symbol = HARP; break;
        case SUN: symbol = SUN; break;
        case COLUMN: symbol = COLUMN; break;
        case BUILDING: symbol = BUILDING; break;
        default: symbol = NO_CHAIN;
    }
}
