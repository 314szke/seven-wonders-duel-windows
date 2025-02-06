#pragma once


#include "../enums/player_id.h"
#include "../game/game.h"
#include "../player/player.h"


class GameManager {
public:
    GameManager(Game& game_ref, const OrderManager& order_manager);
    
    void initalizeGame();

    bool gameIsOn() const;
    void showTable() const;
    void handleTurn();

private:
    void initializePlayer(const PlayerID player_id);
    void playerSwap();
    void playerAction(std::unique_ptr<Player>& player);
    void handleCard(std::unique_ptr<Player>& player, const Card* card);

    Game& game;

    PlayerID current_player;
    PlayerID next_player;

    std::vector<std::unique_ptr<Player>> players;
};
