#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "map.h"
#include "common.h"
#include "level.h"
#include "player.h"
#include "inputhandler.h"
//#include "" // toxin
#include <thread>
#include <vector>
#include <memory>

// declaration for Player and Toxin class
//class Player;
//class Toxin;


class GameEngine{
private:
    std::atomic<int> curr_level;
    std::atomic<int> total_score;
    Map gameMap;
    Player player;
    std::vector <std::thread> gameThread;
    //std::vector<std::unique_ptr<Toxin>> toxins;
    std::unique_ptr<InputHandler> inputHandler;

    // for multi-threading...
    std::vector<std::thread> gameThreads;
    std::atomic<bool> gameRunning{false};
    
public:
    GameEngine();
    ~GameEngine();
    // main loop
    void initializeGame();
    void startGame();
    void stopGame();
    void cleanup();
    // thread management
    void startAllThread();
    void stopAllThread();
    //thread
    void inputThread();
    void gameControllerThread();
    void toxinThread();

    
    // fetch toxin parameters here! 
    int getToxinSpeed() const;
    int getToxinDetectionRange() const;

    // game state
    void setGameState(GameState state);
    bool isGameRunning() const {return gameRunning;}
    int getCurrentLevel() const{return curr_level;}
    int getTotalScore() const{return total_score;}
    
    // game logic
    void checkCollisions();
    void checkCookieCollection();
    void handlePlayerDeath();
    void levelComplete();
    void gameOver();

    void renderGame();

    // this is left for other thread
    Map& getMap() {return gameMap;}
};
#endif