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

    void declareWinner();
    
private:
    void initializePlayer(const PlayerID player_id);
    void wonderSelection();
    void wonderSelectionRound();
    void selectWonder(const PlayerID player_id, const std::vector<std::shared_ptr<const Wonder>>& wonders);

    void playerSwap();
    void playerAction(std::unique_ptr<Player>& player);
    
    void handleAction(std::unique_ptr<Player>& player, const PlayerAction& action);
    void handleCardColor(std::unique_ptr<Player>& player, std::shared_ptr<const Card> card);
    void handleCardGain(std::unique_ptr<Player>& player, std::shared_ptr<const Card> card);
    void handleWonder(std::unique_ptr<Player>& player, std::shared_ptr<const Wonder> wonder);

    void handleGuildMoney(const GuildAction action);
    void addGuildMoneyForCard(const CardColor card_color);
    void handleGuildVictoryPoints(const PlayerID player_id);
    void addGuildVictoryPointsForCard(const CardColor card_color);

    void handleProgressCoinPick(std::unique_ptr<Player>& player);

    void checkForWinner();
    void countVictoryPoints(const PlayerID player_id);
    void announceWinner(const PlayerID player_id) const;

    Game& game;

    PlayerID winner;
    PlayerID current_player;
    PlayerID next_player;

    std::vector<std::unique_ptr<Player>> players;
    std::vector<uint32_t> victory_points;
};
