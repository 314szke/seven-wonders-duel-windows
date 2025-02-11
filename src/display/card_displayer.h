#pragma once

#include "../deck/card.h"


class CardDisplayer {
public:
	static void Show(std::shared_ptr<const Card> card);
	static void Show(const std::vector<std::shared_ptr<const Card>>& cards);
	static void PrintChainSymbol(const ChainSymbol symbol);
	static void PrintScienceSymbol(const ScienceSymbol symbol);
	static void PrintMaterial(const uint32_t material);
	static void PrintMaterials(const MaterialBundle bundle);
	static void PrintProductionDeal(const MaterialBundle bundle);
	static void PrintHybridProduction(const MaterialBundle bundle);
	static void PrintColor(const CardColor color);
};