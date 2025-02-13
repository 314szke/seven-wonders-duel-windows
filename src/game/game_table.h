#pragma once

#include <vector>

#include "progress_coin.h"
#include "../enums/player_id.h"
#include "../finance/bank.h"
#include "../management/order_manager.h"


class GameTable {
public:
    GameTable(const OrderManager& order_manager);

    void attack(const PlayerID attacker_id, const PlayerID defender_id, Bank& bank, uint32_t severity);

    uint32_t getMilitaryPoints(const PlayerID player_id) const;
    uint32_t getMilitaryVictoryPoints(const PlayerID player_id) const;
    bool isMilitarySuperior(const PlayerID player_id) const;
    bool isMilitaryWinner(const PlayerID player_id) const;

private:
    std::vector<int> military_points;
    std::vector<uint32_t> penalty;
    std::vector<ProgressCoin> progress_coins;
};
