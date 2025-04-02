#include <gtest/gtest.h>

#include "../src/constants.h"
#include "../src/finance/bank.h"


class BankTest : public testing::Test {
protected:
	Bank bank;
};

TEST_F(BankTest, Initialization) {
	EXPECT_EQ(bank.creditInfo(SIMON), PLAYER_START_FUND);
	EXPECT_EQ(bank.creditInfo(ENIKO), PLAYER_START_FUND);

	EXPECT_EQ(bank.getCardExchangeRate(SIMON), INITIAL_CARD_EXCHANGE_RATE);
	EXPECT_EQ(bank.getCardExchangeRate(ENIKO), INITIAL_CARD_EXCHANGE_RATE);
}

TEST_F(BankTest, CollectZero) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	bank.collectFrom(SIMON, 0);
	EXPECT_EQ(bank.creditInfo(SIMON), current_fund);

	current_fund = bank.creditInfo(ENIKO);
	bank.collectFrom(ENIKO, 0);
	EXPECT_EQ(bank.creditInfo(ENIKO), current_fund);
}

TEST_F(BankTest, CollectAllFunds) {
	bank.collectFrom(SIMON, bank.creditInfo(SIMON));
	EXPECT_EQ(bank.creditInfo(SIMON), 0);

	bank.collectFrom(ENIKO, bank.creditInfo(ENIKO));
	EXPECT_EQ(bank.creditInfo(ENIKO), 0);
}

TEST_F(BankTest, CollectTooMuch) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	EXPECT_ANY_THROW(bank.collectFrom(SIMON, (current_fund + 1)));

	current_fund = bank.creditInfo(ENIKO);
	EXPECT_ANY_THROW(bank.collectFrom(ENIKO, (current_fund + 1)));
}

TEST_F(BankTest, PayZero) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	bank.payTo(SIMON, 0);
	EXPECT_EQ(bank.creditInfo(SIMON), current_fund);

	current_fund = bank.creditInfo(ENIKO);
	bank.payTo(ENIKO, 0);
	EXPECT_EQ(bank.creditInfo(ENIKO), current_fund);
}

TEST_F(BankTest, PayWithinFund) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	uint32_t amount = 1;

	bank.payTo(SIMON, amount);
	EXPECT_EQ(bank.creditInfo(SIMON), (current_fund + amount));

	current_fund = bank.creditInfo(ENIKO);
	bank.payTo(ENIKO, amount);
	EXPECT_EQ(bank.creditInfo(ENIKO), (current_fund + amount));
}

TEST_F(BankTest, PayTooMuch) {
	uint32_t too_much_fund = INITIAL_BANK_FUNDS + 1;
	EXPECT_ANY_THROW(bank.payTo(SIMON, too_much_fund));
	EXPECT_ANY_THROW(bank.payTo(ENIKO, too_much_fund));
}

TEST_F(BankTest, IncreaseExchangeRate) {
	uint32_t current_rate = bank.getCardExchangeRate(SIMON);
	bank.increaseExchangeRateFor(SIMON);
	EXPECT_EQ(bank.getCardExchangeRate(SIMON), (current_rate + 1));

	current_rate = bank.getCardExchangeRate(ENIKO);
	bank.increaseExchangeRateFor(ENIKO);
	EXPECT_EQ(bank.getCardExchangeRate(ENIKO), (current_rate + 1));
}

TEST_F(BankTest, ExchangeCard) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	uint32_t current_rate = bank.getCardExchangeRate(SIMON);
	bank.exchangeCard(SIMON);
	EXPECT_EQ(bank.creditInfo(SIMON), (current_fund + current_rate));

	current_fund = bank.creditInfo(ENIKO);
	current_rate = bank.getCardExchangeRate(ENIKO);
	bank.exchangeCard(ENIKO);
	EXPECT_EQ(bank.creditInfo(ENIKO), (current_fund + current_rate));
}

TEST_F(BankTest, GivePayablePenalty) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	uint32_t remaining_fund = 1;
	
	bank.givePenalty(SIMON, (current_fund - remaining_fund));
	EXPECT_EQ(bank.creditInfo(SIMON), remaining_fund);

	current_fund = bank.creditInfo(ENIKO);
	bank.givePenalty(ENIKO, (current_fund - remaining_fund));
	EXPECT_EQ(bank.creditInfo(ENIKO), remaining_fund);
}

TEST_F(BankTest, GiveTooMuchPenalty) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	bank.givePenalty(SIMON, (current_fund + 1));
	EXPECT_EQ(bank.creditInfo(SIMON), 0);

	current_fund = bank.creditInfo(ENIKO);
	bank.givePenalty(ENIKO, (current_fund + 1));
	EXPECT_EQ(bank.creditInfo(ENIKO), 0);
}

TEST_F(BankTest, CreditCheck) {
	uint32_t current_fund = bank.creditInfo(SIMON);
	EXPECT_TRUE(bank.creditCheck(SIMON, 0));
	EXPECT_TRUE(bank.creditCheck(SIMON, current_fund));
	EXPECT_FALSE(bank.creditCheck(SIMON, (current_fund + 1)));
	
	current_fund = bank.creditInfo(ENIKO);
	EXPECT_TRUE(bank.creditCheck(ENIKO, 0));
	EXPECT_TRUE(bank.creditCheck(ENIKO, current_fund));
	EXPECT_FALSE(bank.creditCheck(ENIKO, (current_fund + 1)));
}
