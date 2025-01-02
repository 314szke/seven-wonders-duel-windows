#include "bank.h"

#include <stdexcept>

#include "../enums/exception_types.h"
#include "../enums/player_id.h"


Bank::Bank() :
    fund(INITIAL_FUNDS),
    player_money(PlayerID::NUMBER_OF_PLAYERS)
{
    player_money[PlayerID::SIMON] = PLAYER_START_FUND;
    player_money[PlayerID::ENIKO] = PLAYER_START_FUND;
}

void Bank::collectFrom(const uint32_t player_id, const uint32_t value) {
    if (value > player_money[player_id]) {
        throw ExceptionType::PLAYER_OUT_OF_BUDGET;
    }

    fund += value;
    player_money[player_id] -= value;
}

void Bank::payTo(const uint32_t player_id, const uint32_t value) {
    if (value > fund) {
        throw ExceptionType::BANK_OUT_OF_FUNDS;
    }

    fund -= value;
    player_money[player_id] += value;
}

void Bank::giveMilitaryPenalty(const uint32_t player_id, const uint32_t value)
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

bool Bank::creditCheck(const uint32_t player_id, const uint32_t value) const
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
