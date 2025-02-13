#include "player_displayer.h"

#include <iostream>

#include "../enums/material_types.h"
#include "../enums/chain_symbols.h"
#include "../enums/science_symbols.h"
#include "../display/card_displayer.h"


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
        std::cout << " ";
        CardDisplayer::PrintHybridProduction(bundle);
    }
    std::cout << PLAYER_INFO_SEPARATOR;
}

void PlayerDisplayer::showSymbols(const std::unique_ptr<Player>& player)
{
	for (ChainSymbol symbol : player->chain_symbols) {
        std::cout << " ";
        CardDisplayer::PrintChainSymbol(symbol);
	}
    std::cout << PLAYER_INFO_SEPARATOR;

    for (ScienceSymbol symbol : player->science_symbols) {
        std::cout << " ";
        CardDisplayer::PrintScienceSymbol(symbol);
    }
    std::cout << PLAYER_INFO_SEPARATOR;
}
