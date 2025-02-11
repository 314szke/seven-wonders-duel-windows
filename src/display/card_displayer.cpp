#include "card_displayer.h"

#include <iostream>


void CardDisplayer::Show(std::shared_ptr<const Card> card)
{
	std::cout << "Card " << card->info.ID << std::endl;
    std::cout << "    color  ";
    PrintColor(card->info.color);
    std::cout << std::endl;

	std::cout << "    cost   ";
    std::cout << "$:" << card->cost.money << ", materials:[";
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (card->cost.materials.materials[idx] > 0) {
            for (uint32_t jdx = 0; jdx < card->cost.materials.materials[idx]; jdx++) {
                PrintMaterial(idx);
            }
        }
    }
    std::cout << "]";

	if (card->cost.symbol != NO_CHAIN) {
        std::cout << " | symbol:";
		PrintChainSymbol(card->cost.symbol);
	}
    std::cout << std::endl;


	std::cout << "    gain   ";
    std::cout << "$:" << card->gain.money << ", M:" << card->gain.military_point << ", V:" << card->gain.victory_point;
    std::cout << ", materials:[";
    if (card->gain.production_deal) {
        PrintProductionDeal(card->gain.materials);
    } else if (card->gain.hybrid_production) {
        PrintHybridProduction(card->gain.materials);
    } else {
        PrintMaterials(card->gain.materials);
    }
    
    std::cout << "], chain_symbol:[";
    CardDisplayer::PrintChainSymbol(card->gain.chain_symbol);
    std::cout << "], science_symbol:[";
    CardDisplayer::PrintScienceSymbol(card->gain.science_symbol);
    std::cout << "]";
    std::cout << std::endl;
}

void CardDisplayer::Show(const std::vector<std::shared_ptr<const Card>>& cards)
{
    for (uint32_t idx = 0; idx < cards.size(); idx++) {
        if (cards[idx]->state == CARD_VISIBLE) {
            Show(cards[idx]);
        }
    }
}

void CardDisplayer::PrintChainSymbol(const ChainSymbol symbol)
{
    switch (symbol) {
        case VASE: std::cout << "VASE"; break;
        case SWORD: std::cout << "SWORD"; break;
        case TOWER: std::cout << "TOWER"; break;
        case HORSESHOE:std::cout << "HORSESHOE"; break;
        case BOOK: std::cout << "BOOK"; break;
        case GEAR: std::cout << "GEAR"; break;
        case MOON: std::cout << "MOON"; break;
        case WATER: std::cout << "WATER"; break;
        case MASK: std::cout << "MASK"; break;
        case BARREL: std::cout << "BARREL"; break;
        case TARGET: std::cout << "TARGET"; break;
        case HELMET: std::cout << "HELMET"; break;
        case TEAPOT: std::cout << "TEAPOT"; break;
        case HARP: std::cout << "HARP"; break;
        case SUN:  std::cout << "SUN"; break;
        case COLUMN: std::cout << "COLUMN"; break;
        case BUILDING: std::cout << "BUILDING"; break;
    }
}

void CardDisplayer::PrintScienceSymbol(const ScienceSymbol symbol)
{
    switch (symbol) {
        case GLOBE: std::cout << "GLOBE"; break;
        case WHEEL: std::cout << "WHEEL"; break;
        case WATCH: std::cout << "WATCH"; break;
        case MORTAR: std::cout << "MORTAR"; break;
        case RULER: std::cout << "RULER"; break;
        case PEN: std::cout << "PEN"; break;
    }
}

void CardDisplayer::PrintMaterial(const uint32_t material)
{
    switch (material) {
        case WOOD: std::cout << "W"; break;
        case CLAY: std::cout << "C"; break;
        case ROCK: std::cout << "R"; break;
        case PAPER: std::cout << "P"; break;
        case GLASS: std::cout << "G"; break;
    }
}

void CardDisplayer::PrintMaterials(const MaterialBundle bundle)
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (bundle.materials[idx] > 0) {
            for (uint32_t jdx = 0; jdx < bundle.materials[idx]; jdx++) {
                PrintMaterial(idx);
            }
        }
    }
}

void CardDisplayer::PrintProductionDeal(const MaterialBundle bundle)
{
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (bundle.materials[idx] > 0) {
            std::cout << "(";
            PrintMaterial(idx);
            std::cout << ")";
        }
    }
}

void CardDisplayer::PrintHybridProduction(const MaterialBundle bundle)
{
    bool first = true;
    for (uint32_t idx = 0; idx < NUMBER_OF_MATERIALS; idx++) {
        if (bundle.materials[idx] > 0) {
            if (first) {
                first = false;
            } else {
                std::cout << "/";
            }
            PrintMaterial(idx);
        }
    }
}

void CardDisplayer::PrintColor(const CardColor color)
{
    switch (color) {
        case BROWN: std::cout << "BROWN"; break;
        case GREY: std::cout << "GREY"; break;
        case YELLOW: std::cout << "YELLOW"; break;
        case RED: std::cout << "RED"; break;
        case GREEN: std::cout << "GREEN"; break;
        case BLUE: std::cout << "BLUE"; break;
        case PURPLE: std::cout << "PURPLE"; break;
    }
}
