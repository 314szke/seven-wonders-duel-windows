#pragma once

#include <vector>

#include "../enums/player_id.h"


class Bank {
public:
    Bank();

    void collectFrom(const PlayerID player_id, const uint32_t value);
    void exchangeCard(const PlayerID player_id);
    void increaseExchangeRateFor(const PlayerID player_id);
    void giveMilitaryPenalty(const PlayerID player_id, const uint32_t value);

    bool creditCheck(const PlayerID player_id, const uint32_t value) const;
    uint32_t creditInfo(const PlayerID player_id) const;

private:
    void payTo(const PlayerID player_id, const uint32_t value);

    uint32_t fund;
    std::vector<uint32_t> player_money;
    std::vector<uint32_t> card_exchange_rate;
};

