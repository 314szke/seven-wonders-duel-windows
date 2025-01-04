#pragma once


#include "../enums/player_id.h"
#include "../display/player_displayer.h"
#include "../game/game.h"
#include "../player/player.h"


class GameManager {
public:
    GameManager(Game& game_ref);
    
    void initializePlayers();
    void initalizeGame();

    bool gameIsOn();
    void showTable();
    void handleTurn();

private:
    void handleCard(std::unique_ptr<Player>& player, const uint32_t card_id);

    Game& game;

    std::unique_ptr<Player> Simon;
    std::unique_ptr<Player> Eniko;

    PlayerID current_player;
    PlayerID next_player;

    PlayerDisplayer player_displayer;
};
