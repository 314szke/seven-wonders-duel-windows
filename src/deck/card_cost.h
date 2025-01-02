#pragma once

#include "../enums/chain_symbols.h"
#include "../finance/material_bundle.h"


class CardCost {
public:
    CardCost(const uint32_t money_cost, const MaterialBundle& material_cost, const int symbol_cost);

    uint32_t money;
    MaterialBundle materials;
    ChainSymbol symbol;
};
