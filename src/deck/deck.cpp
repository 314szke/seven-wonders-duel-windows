#include "deck.h"

#include "../constants.h"


Deck::Deck(const OrderManager& order_manager) :
	manager(order_manager),
	visible_cards(MAX_NUMBER_OF_VISIBLE_CARDS)
{}

void Deck::prepareTheFirstAge()
{
}

void Deck::prepareTheSecondAge()
{
}

void Deck::prepareTheThirdAge()
{
}

void Deck::takeCard(const uint32_t visible_card_idx)
{
}
