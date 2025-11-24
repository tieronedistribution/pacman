#include "GameEngine.h"
#include<iostream>
#include<chrono>
#include<thread>

SharedGameData g_sharedData; // use 'extern' to fetch the date!
std::mutex g_displayMutex;
std::atomic<bool> gameRunning(false);

GameEngine::GameEngine()
    : gameMap(), player(), gameRunning(false), curr_level(1), total_score(0){
    initializeGame();
}

 
GameEngine::~GameEngine(){
    // this will stop the game as soon as the object is not in scope.
    cleanup();
}

void GameEngine::initializeGame(){
    //initialize the game
    std::cout << "Initializing Pacman Game..." << std::endl;
    
    // reset the game
    g_sharedData.score = 0;
    g_sharedData.lives = 3;
    g_sharedData.currentLevel = 1; //
    g_sharedData.gameState = GameState::RUNNING;
    
    // initialize the map
    gameMap.initializeLevel(1);
    gameRunning = true;
    std::cout << "Game initialized successfully!" << std::endl;
}

//void GameEngine::select_level(){
    // level selection and display
   // std::cout << "Level chose:" << LevelSelector::level_to_string(curr_level) << std::endl;
//}

void GameEngine::startGame(){
    std::cout << "Starting game threads..." << std::endl;
    startAllThread();
}

void GameEngine::stopGame(){
    std::cout << "Stopping game..." << std::endl;
    gameRunning = false;
    g_sharedData.gameState = GameState::GAME_OVER;
    stopAllThread();
}

// thread 2: input handler
void GameEngine::inputThread(){
    //std::cout << "Input Thread (Thread 2) started" << std::endl;
    inputHandler->startInputThread();
    while(gameRunning){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (player.getLives() <= 0){
            gameRunning = false;
            break;
        }
    }
    inputHandler->stopInputThread();
    //std::cout << "Input Thread (Thread 2) stopped" << std::endl;
}

// thread 3: game controller
void GameEngine::gameControllerThread(){
    //std::cout << "Game Controller Thread (Thread 3) started" << std::endl;
    auto lastUpdateTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds updateInterval(100); // 10 FPS for game logic
    
    while(gameRunning){
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = currentTime - lastUpdateTime;
        if (elapsedTime >= updateInterval){
            checkCollisions();
            checkCookieCollection();
            renderGame();
            lastUpdateTime = currentTime;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (player.getLives() <= 0){
            gameOver();
            break;
        }
        if (gameMap.getCookies().empty()){
            levelComplete();
        }
    }
    //std::cout << "Game Controller Thread (Thread 3) stopped" << std::endl;
}

// thread 4: toxins
void GameEngine::toxinThread(){
    //
    while (g_sharedData.gameState == GameState::RUNNING){
            // Toxins




            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
}



void GameEngine::startAllThread(){
    gameThreads.emplace_back(&GameEngine::inputThread, this);
    gameThreads.emplace_back(&GameEngine::gameControllerThread, this);
    //gameThread.emplace_back(&GameEngine::toxinThread, this);
    std::cout << "All game threads started!" << std::endl;
}

void GameEngine::stopAllThread(){
    // stop all the thread
    for (auto& thread : gameThread){
        if (thread.joinable()){
            thread.join();
        }
    }
    gameThread.clear();
}

// game logic
void GameEngine::checkCollisions() {
    Position playerPos = player.getPosition();
    // check if collide with the toxins
    //for (const auto& toxin : toxins) {
    //    if (toxin && toxin->getPosition() == playerPos) {
    //        std::cout << "Collision with ghost detected!" << std::endl;
    //        handlePlayerDeath();
    //        break;
    //    }
    //}
}

void GameEngine::handlePlayerDeath() {
    std::cout << "Wasted" << std::endl;
    player.loseLife();
    if (player.getLives() > 0) {
        std::cout << "Respawning player..." << std::endl;
        player.respawn();
//        for (auto& toxin : toxins) {
//            if (toxin) {
 //               toxin->resetPosition();
 //           }
 //       }
    }
}

void GameEngine::checkCookieCollection() {
    //
}

void GameEngine::levelComplete() {
    std::cout << "=== LEVEL " << curr_level << " COMPLETE! ===" << std::endl;
    curr_level++;
    total_score += curr_level * 100; // 关卡完成奖励
    
    std::cout << "Advancing to level " << curr_level << std::endl;
    std::cout << "Total score: " << total_score << std::endl;
    gameMap.initializeLevel(curr_level);
    player.resetPosition();
    
    // reset toixn
    
}



int GameEngine::getToxinSpeed() const{
    //fetch the toxin speed for different level (in millisecond here!)
    switch(curr_level){
        case level::EASY: return 500;// you can change the value as you want!
        case level::MODERATE: return 300;// you can change the value as you want!
        case level::HARD: return 100;// you can change the value as you want!
        default: return 500;// you can change the value as you want!
    }
}

int GameEngine::getToxinDetectionRange() const{
    switch(curr_level){
        case level::EASY: return 2;// you can change the value as you want!
        case level::MODERATE: return 5;// you can change the value as you want!
        case level::HARD: return 8;// you can change the value as you want!
        default: return 2;// you can change the value as you want!
    }
}

void GameEngine::setGameState(GameState state){
    g_sharedData.gameState = state;
}

void GameEngine::renderGame(){
    system("clear");
    std::cout << "=== PACMAN === Level: " << curr_level << " Score: " << total_score << " Lives: " << player.getLives() << std::endl;
    std::cout << "Controls: WASD to move, Q to quit" << std::endl << std::endl;
    gameMap.display();
    std::cout << std::endl;
}

void GameEngine::cleanup(){
    stopGame();
    //std::cout << "Game engine cleaned up!" << std::endl;
}