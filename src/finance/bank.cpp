#include "bank.h"

#include "../constants.h"
#include "../enums/exception_types.h"


Bank::Bank() :
    fund(INITIAL_BANK_FUNDS),
    player_money(NUMBER_OF_PLAYERS)
{
    player_money[SIMON] = PLAYER_START_FUND;
    player_money[ENIKO] = PLAYER_START_FUND;
}

void Bank::collectFrom(const PlayerID player_id, const uint32_t value) {
    if (value > player_money[player_id]) {
        throw PLAYER_OUT_OF_BUDGET;
    }

    fund += value;
    player_money[player_id] -= value;
}

void Bank::payTo(const PlayerID player_id, const uint32_t value) {
    if (value > fund) {
        throw BANK_OUT_OF_FUNDS;
    }

    fund -= value;
    player_money[player_id] += value;
}

void Bank::giveMilitaryPenalty(const PlayerID player_id, const uint32_t value)
{
    if (value > player_money[player_id]) {
        fund += player_money[player_id];
        player_money[player_id] = 0;
    }
    else {
        fund += value;
        player_money[player_id] -= value;
    }
}

bool Bank::creditCheck(const PlayerID player_id, const uint32_t value) const
{
    if (player_money[player_id] < value) {
        return false;
    }
    return true;
}

const std::vector<uint32_t>& Bank::creditInfo() const
{
    return player_money;
}
