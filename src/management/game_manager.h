#pragma once

#include "order_manager.h"

#include "../finance/bank.h"
#include "../finance/market.h"
#include "../game/game_table.h"


class GameManager {
public:
    GameManager();

private:
    OrderManager order_manger;
    Bank bank;
    Market market;
    GameTable table;
};
