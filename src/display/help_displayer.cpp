#include "help_displayer.h"

#include <iostream>


void HelpDisplayer::Show()
{
	std::cout << "You are playing 7 wonders Duel, a two-player game." << std::endl;
	std::cout << "In this game, each player has a city. Your goal is to develop your city faster than your opponent." << std::endl;
	std::cout << "You can win by either: - having an overpowering military (= 9 military points) to conquer your adversary" << std::endl;
	std::cout << "                       - being a nerd++ (= you own 6 different science symbols)" << std::endl;
	std::cout << "                       - having a better city at the end of the game (= have more victory points than the opponent)" << std::endl << std::endl;
	//
	std::cout << "The game has three stages named: first age, second age, and third age." << std::endl;
	std::cout << "Each age has 20 cards in a specific arrangement." << std::endl;
	std::cout << "In each arrangement, a card is only accessible if there are no cards below it on either side." << std::endl;
	std::cout << "Some cards are initially hidden (marked as ??). They become visible once they are accessible." << std::endl << std::endl;
	//
	std::cout << "The players take actions in turns." << std::endl;
	std::cout << "During each turn, the current player may: - take an accesible card from the table and use it (given that the player can pay for the card)" << std::endl;
	std::cout << "                                          - discard an accessible card to gain money" << std::endl;
	std::cout << "                                          - take an accessible card to build a wonder for your city" << std::endl << std::endl;
	//
	std::cout << "The game displays the current deck corresponding to the current age by the cards' id numbers." << std::endl;
	std::cout << "Below the deck, the game shows the players' statuses." << std::endl;
	std::cout << "The status bar has 5 segments separated by a | symbol. The segments are: basic attributes | material production | hybrid production | chain symbols | science symbols |." << std::endl;
	std::cout << "Staus symbol explanations: $ - the amount of MONEY that the player has" << std::endl;
	std::cout << "                           M - the amount of MILITARY points that the player has" << std::endl;
	std::cout << "                           V - the amount of VICTORY points that the player has" << std::endl;
	std::cout << "                           E - the exchange rate of discarded cards (increases by 1 for each YELLOW card you own)" << std::endl;
	std::cout << "                           W - the amount of WOOD you produce" << std::endl;
	std::cout << "                           C - the amount of CLAY you produce" << std::endl;
	std::cout << "                           R - the amount of ROCK you produce" << std::endl;
	std::cout << "                           P - the amount of PAPER you produce" << std::endl;
	std::cout << "                           G - the amount of GLASS you produce" << std::endl;
	std::cout << "If a material is in brackets (for example: (W)), it shows that you can purchase this material for a fixed price of 1." << std::endl;
	std::cout << "If you do not have brackets around a material and you want to purchase it, you have to pay (2 + (production difference with the other player))." << std::endl;
	std::cout << "Hybrid production (for example: W/C/R) means that during each turn you can decide to produce ONE of the listed materials." << std::endl;
	std::cout << "(The computer automatically chooses the best hybrid production to minimize the card purchase cost.)" << std::endl << std::endl;
	//
	std::cout << "For a more detailed game guide please visit: https://cdn.1j1ju.com/medias/1a/ba/6b-7-wonders-duel-rules.pdf" << std::endl;
}
