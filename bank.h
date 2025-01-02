#pragma once

#include <stdint.h>
#include <vector>


#define INITIAL_FUNDS 72
#define PLAYER_START_FUND 7


class Bank {
public:
    Bank();

    void collectFrom(const uint32_t player_id, const uint32_t value);
    void payTo(const uint32_t player_id, const uint32_t value);
    void giveMilitaryPenalty(const uint32_t player_id, const uint32_t value);

    bool creditCheck(const uint32_t player_id, const uint32_t value) const;
    const std::vector<uint32_t>& creditInfo() const;

private:
    uint32_t fund;
    std::vector<uint32_t> player_money;
};

