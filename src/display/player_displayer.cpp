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
    std::cout << " V:" << player->getVictoryPoints() << PLAYER_INFO_SEPARATOR;

	showMaterials(player, game);
    showSymbols(player);

	std::cout << std::endl;
}

void PlayerDisplayer::showMaterials(const std::unique_ptr<Player>& player, const Game& game)
{	
    std::cout << " W:" << game.market.getProducedAmount(player->ID, WOOD);
	std::cout << " C:" << game.market.getProducedAmount(player->ID, CLAY);
	std::cout << " R:" << game.market.getProducedAmount(player->ID, ROCK);
	std::cout << " P:" << game.market.getProducedAmount(player->ID, PAPER);
	std::cout << " G:" << game.market.getProducedAmount(player->ID, GLASS);
	std::cout << PLAYER_INFO_SEPARATOR;
}

void PlayerDisplayer::showSymbols(const std::unique_ptr<Player>& player)
{
	for (ChainSymbol symbol : player->getChainSymbols()) {
        switch (symbol) {
            case VASE: std::cout << "VASE "; break;
            case SWORD: std::cout << "SWORD "; break;
            case TOWER: std::cout << "TOWER "; break;
            case HORSESHOE:std::cout << "HORSESHOE "; break;
            case BOOK: std::cout << "BOOK "; break;
            case GEAR: std::cout << "GEAR "; break;
            case MOON: std::cout << "MOON "; break;
            case WATER: std::cout << "WATER "; break;
            case MASK: std::cout << "MASK "; break;
            case BARREL: std::cout << "BARREL "; break;
            case TARGET: std::cout << "TARGET "; break;
            case HELMET: std::cout << "HELMET "; break;
            case TEAPOT: std::cout << "TEAPOT "; break;
            case HARP: std::cout << "HARP "; break;
            case SUN:  std::cout << "SUN "; break;
            case COLUMN: std::cout << "COLUMN "; break;
            case BUILDING: std::cout << "BUILDING "; break;
        }
	}
    
    if (player->getChainSymbols().size() > 0) {
        std::cout << PLAYER_INFO_SEPARATOR;
    }

    for (ScienceSymbol symbol : player->getScienceSymbols()) {
        switch (symbol) {
            case GLOBE: std::cout << "GLOBE "; break;
            case WHEEL: std::cout << "WHEEL "; break;
            case WATCH: std::cout << "WATCH "; break;
            case MORTAR: std::cout << "MORTAR "; break;
            case RULER: std::cout << "RULER "; break;
            case PEN: std::cout << "PEN "; break;
        }
    }

    if (player->getScienceSymbols().size() > 0) {
        std::cout << PLAYER_INFO_SEPARATOR;
    }
}
