#pragma once

#include "../deck/card.h"


class CardDisplayer {
public:
	static void Show(std::shared_ptr<const Card> card);
	static void PrintChainSymbol(const ChainSymbol symbol);
	static void PrintScienceSymbol(const ScienceSymbol symbol);
	static void PrintMaterial(const uint32_t material);
	static void PrintColor(const CardColor color);
};