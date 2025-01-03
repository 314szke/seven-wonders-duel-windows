#pragma once

#include "order_manager.h"

#include "../deck/deck.h"
#include "../finance/bank.h"
#include "../finance/market.h"
#include "../game/game_table.h"


class GameManager {
public:
    GameManager();
    
    void setTheFirstStage();
    void setTheSecondStage();
    void setTheThirdStage();

    bool gameIsOn();
    void showTable();

    void takeCardFromConsol(const uint32_t consol_card_id);

private:
    const int random_seed;
    OrderManager order_manger;

    Deck deck;
    Bank bank;
    Market market;
    GameTable table;
};
