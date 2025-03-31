#include "card_gain.h"


CardGain::CardGain(
	const uint32_t card_money, 
	const uint32_t card_victory_point, 
	const uint32_t card_military_point, 
//
	const int card_chain_symbol, 
	const int card_science_symbol, 
//
	const bool card_production_deal, 
	const bool card_hybrid_production,
	const MaterialBundle& card_materials, 
//	
    const int card_action, 
	const int card_guild_action) :
//
	money(card_money),
	victory_point(card_victory_point),
	military_point(card_military_point),
//
    production_deal(card_production_deal),
    hybrid_production(card_hybrid_production),
    materials(card_materials)
{
    switch (card_chain_symbol) {
        case VASE: chain_symbol = VASE; break;
        case SWORD: chain_symbol = SWORD; break;
        case TOWER: chain_symbol = TOWER; break;
        case HORSESHOE: chain_symbol = HORSESHOE; break;
        case BOOK: chain_symbol = BOOK; break;
        case GEAR: chain_symbol = GEAR; break;
        case MOON: chain_symbol = MOON; break;
        case WATER: chain_symbol = WATER; break;
        case MASK: chain_symbol = MASK; break;
        case BARREL: chain_symbol = BARREL; break;
        case TARGET: chain_symbol = TARGET; break;
        case HELMET: chain_symbol = HELMET; break;
        case TEAPOT: chain_symbol = TEAPOT; break;
        case HARP: chain_symbol = HARP; break;
        case SUN: chain_symbol = SUN; break;
        case COLUMN: chain_symbol = COLUMN; break;
        case BUILDING: chain_symbol = BUILDING; break;
        default: chain_symbol = NO_CHAIN;
    }

    switch (card_science_symbol) {
        case GLOBE: science_symbol = GLOBE; break;
        case WHEEL: science_symbol = WHEEL; break;
        case WATCH: science_symbol = WATCH; break;
        case MORTAR: science_symbol = MORTAR; break;
        case RULER: science_symbol = RULER; break;
        case PEN: science_symbol = PEN; break;
        default: science_symbol = NO_SCIENCE;
    }
    
    switch (card_action) {
        case WONDER_MONEY: action = WONDER_MONEY; break;
        case BROWN_MONEY: action = BROWN_MONEY; break;
        case GREY_MONEY: action = GREY_MONEY; break;
        case YELLOW_MONEY: action = YELLOW_MONEY; break;
        case RED_MONEY: action = RED_MONEY; break;
        default: action = NO_ACTION;
    }

    switch (card_guild_action) {
        case MONEY_POINT: guild_action = MONEY_POINT; break;
        case WONDER_POINT: guild_action = WONDER_POINT; break;
        case BROWN_GREY_POINT: guild_action = BROWN_GREY_POINT; break;
        case YELLOW_POINT: guild_action = YELLOW_POINT; break;
        case RED_POINT: guild_action = RED_POINT; break;
        case GREEN_POINT: guild_action = GREEN_POINT; break;
        case BLUE_POINT: guild_action = BLUE_POINT; break;
        default: guild_action = NO_GUILD_ACTION;
    }
}
