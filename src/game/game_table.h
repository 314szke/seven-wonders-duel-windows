#pragma once

#include <vector>

#include "progress_coin.h"
#include "../enums/player_id.h"
#include "../finance/bank.h"


#define COIN_COUNTER 10
#define FIRST_PENALTY 2
#define SECOND_PENALTY 5
#define MILITARY_WIN 9


class GameTable {
public:
    GameTable(const std::vector<uint32_t>& visible_coin_IDs);

    void attack(const PlayerID attacker_id, const PlayerID defender_id, Bank& bank, uint32_t severity);
    bool isMilitarySuperior(const PlayerID player_id) const;
    bool isMilitaryWinner(const PlayerID player_id) const;

private:
    std::vector<int> military_points;
    std::vector<uint32_t> penalty;
    std::vector<ProgressCoin> progress_coins;
};
