#include "bank.h"

#include "../constants.h"
#include "../enums/exception_types.h"


Bank::Bank() :
    fund(INITIAL_BANK_FUNDS),
    player_money(NUMBER_OF_PLAYERS),
    card_exchange_rate(NUMBER_OF_PLAYERS)
{
    player_money[SIMON] = PLAYER_START_FUND;
    player_money[ENIKO] = PLAYER_START_FUND;

    card_exchange_rate[SIMON] = INITIAL_CARD_EXCHANGE_RATE;
    card_exchange_rate[ENIKO] = INITIAL_CARD_EXCHANGE_RATE;
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

void Bank::exchangeCard(const PlayerID player_id)
{
    payTo(player_id, card_exchange_rate[player_id]);
}

void Bank::increaseExchangeRateFor(const PlayerID player_id)
{
    card_exchange_rate[player_id]++;
}

void Bank::givePenalty(const PlayerID player_id, const uint32_t value)
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

uint32_t Bank::creditInfo(const PlayerID player_id) const
{
    return player_money[player_id];
}

uint32_t Bank::getCardExchangeRate(const PlayerID player_id) const
{
    return card_exchange_rate[player_id];
}

uint32_t Bank::getMoneyVictoryPoints(const PlayerID player_id) const
{
    return player_money[player_id] / 3;
}

