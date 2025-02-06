#include "player_displayer.h"

#include <iostream>

#include "../enums/material_types.h"
#include "../enums/chain_symbols.h"
#include "../enums/science_symbols.h"


constexpr auto PLAYER_INFO_SEPARATOR = " |";

void PlayerDisplayer::Show(const std::unique_ptr<Player>& player, const Game& game)
{
	std::cout << player->name;

	std::cout << " $:" << game.bank.creditInfo(player->ID);
	std::cout << " M:" << game.table.getMilitaryPoints(player->ID);
    std::cout << " V:" << player->victory_points;
    std::cout << " E:" << game.bank.getCardExchangeRate(player->ID);
    std::cout << PLAYER_INFO_SEPARATOR;

    showMaterials(player, game);
    showSymbols(player);

	std::cout << std::endl;
}

void PlayerDisplayer::showMaterials(const std::unique_ptr<Player>& player, const Game& game)
{
    if (game.market.deals[player->ID][WOOD]) {
        std::cout << " (W):" << game.market.produce[player->ID].materials[WOOD];  
    } else {
        std::cout << "  W :" << game.market.produce[player->ID].materials[WOOD];  
    }
    
    if (game.market.deals[player->ID][CLAY]) {
        std::cout << " (C):" << game.market.produce[player->ID].materials[CLAY];
    } else {
        std::cout << "  C :" << game.market.produce[player->ID].materials[CLAY];
    }
    
    if (game.market.deals[player->ID][ROCK]) {
        std::cout << " (R):" << game.market.produce[player->ID].materials[ROCK];
    } else {
        std::cout << "  R :" << game.market.produce[player->ID].materials[ROCK];
    }
    
    if (game.market.deals[player->ID][PAPER]) {
        std::cout << " (P):" << game.market.produce[player->ID].materials[PAPER];
    } else {
        std::cout << "  P :" << game.market.produce[player->ID].materials[PAPER];
    }

    if (game.market.deals[player->ID][GLASS]) {
        std::cout << " (G):" << game.market.produce[player->ID].materials[GLASS];
    } else {
        std::cout << "  G :" << game.market.produce[player->ID].materials[GLASS];
    }
    
    std::cout << PLAYER_INFO_SEPARATOR;

    for (const MaterialBundle& bundle : game.market.hybrid_produce[player->ID]) {
        bool first = true;
        for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
            if (bundle.materials[idx] > 0) {
                if (first) {
                    std::cout << " ";
                    first = false;
                } else {
                    std::cout << "/";
                }

                switch (idx) {
                    case WOOD: std::cout << "W"; break;
                    case CLAY: std::cout << "C"; break;
                    case ROCK: std::cout << "R"; break;
                    case PAPER: std::cout << "P"; break;
                    case GLASS: std::cout << "G"; break;
                }
            }
        }
    }

    if (game.market.hybrid_produce[player->ID].size() > 0) {
        std::cout << PLAYER_INFO_SEPARATOR;
    }
}

void PlayerDisplayer::showSymbols(const std::unique_ptr<Player>& player)
{
	for (ChainSymbol symbol : player->chain_symbols) {
        switch (symbol) {
            case VASE: std::cout << " VASE"; break;
            case SWORD: std::cout << " SWORD"; break;
            case TOWER: std::cout << " TOWER"; break;
            case HORSESHOE:std::cout << " HORSESHOE"; break;
            case BOOK: std::cout << " BOOK"; break;
            case GEAR: std::cout << " GEAR"; break;
            case MOON: std::cout << " MOON"; break;
            case WATER: std::cout << " WATER"; break;
            case MASK: std::cout << " MASK"; break;
            case BARREL: std::cout << " BARREL"; break;
            case TARGET: std::cout << " TARGET"; break;
            case HELMET: std::cout << " HELMET"; break;
            case TEAPOT: std::cout << " TEAPOT"; break;
            case HARP: std::cout << " HARP"; break;
            case SUN:  std::cout << " SUN"; break;
            case COLUMN: std::cout << " COLUMN"; break;
            case BUILDING: std::cout << " BUILDING"; break;
        }
	}
    
    if (player->chain_symbols.size() > 0) {
        std::cout << PLAYER_INFO_SEPARATOR;
    }

    for (ScienceSymbol symbol : player->science_symbols) {
        switch (symbol) {
            case GLOBE: std::cout << " GLOBE"; break;
            case WHEEL: std::cout << " WHEEL"; break;
            case WATCH: std::cout << " WATCH"; break;
            case MORTAR: std::cout << " MORTAR"; break;
            case RULER: std::cout << " RULER"; break;
            case PEN: std::cout << " PEN"; break;
        }
    }

    if (player->science_symbols.size() > 0) {
        std::cout << PLAYER_INFO_SEPARATOR;
    }
}
