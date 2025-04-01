#include <gtest/gtest.h>

#include "../src/constants.h"
#include "../src/finance/bank.h"


class BankTest : public testing::Test {
protected:
	Bank bank;
};

TEST_F(BankTest, Initialization) {
	bank.collectFrom(SIMON, PLAYER_START_FUND);
	bank.collectFrom(ENIKO, PLAYER_START_FUND);
}

TEST_F(BankTest, CollectZero) {
	uint32_t fund_before = bank.creditInfo(SIMON);
	bank.collectFrom(SIMON, 0);
	EXPECT_EQ(bank.creditInfo(SIMON), fund_before);

	fund_before = bank.creditInfo(ENIKO);
	bank.collectFrom(ENIKO, 0);
	EXPECT_EQ(bank.creditInfo(ENIKO), fund_before);
}

TEST_F(BankTest, CollectAllFunds) {
	bank.collectFrom(SIMON, bank.creditInfo(SIMON));
	EXPECT_EQ(bank.creditInfo(SIMON), 0);

	bank.collectFrom(ENIKO, bank.creditInfo(ENIKO));
	EXPECT_EQ(bank.creditInfo(ENIKO), 0);
}