#include "game_table.h"


GameTable::GameTable(const std::vector<uint32_t>& visible_coin_IDs) :
    military_points(NUMBER_OF_PLAYERS),
    penalty(NUMBER_OF_PLAYERS)
{
    military_points[SIMON] = 0;
    military_points[ENIKO] = 0;

    penalty[SIMON] = 0;
    penalty[ENIKO] = 0;

    for (uint32_t idx = 0; idx < COIN_COUNTER; idx++) {
        progress_coins.push_back(ProgressCoin(idx));
    }

    for (uint32_t idx : visible_coin_IDs) {
        progress_coins[idx].setVisible();
    }
}

void GameTable::attack(const PlayerID attacker_id, const PlayerID defender_id, Bank& bank, uint32_t severity)
{
    military_points[attacker_id] += (severity - military_points[defender_id]);
    if (military_points[attacker_id] < 0 ) {
        military_points[attacker_id] = 0;
    }

    military_points[defender_id] -= severity;
    if (military_points[defender_id] < 0 ) {
        military_points[defender_id] = 0;
    }

    if ((military_points[attacker_id] > FIRST_PENALTY) && (penalty[defender_id] < FIRST_PENALTY)) {
        bank.giveMilitaryPenalty(defender_id, FIRST_PENALTY);
        penalty[defender_id] += FIRST_PENALTY;
    }

    if ((military_points[attacker_id] > SECOND_PENALTY) && (penalty[defender_id] < SECOND_PENALTY)) {
        bank.giveMilitaryPenalty(defender_id, SECOND_PENALTY);
        penalty[defender_id] += SECOND_PENALTY;
    }
}

bool GameTable::isMilitarySuperior(const PlayerID player_id) const
{
    if (military_points[player_id] == 0) {
        return false;
    }
    return true;
}

bool GameTable::isMilitaryWinner(const PlayerID player_id) const
{
    if (military_points[player_id] < MILITARY_WIN) {
        return false;
    }
    return true;
}
