#ifndef COMMON_H
#define COMMON_H

#include <mutex>
#include <atomic>
#include <thread>

// game state
enum class GameState {
    RUNNING,
    PAUSED,
    GAME_OVER,
    LEVEL_COMPLETE
};

// movements
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

// position
struct Position {
    int x;
    int y;
    Position(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// these data can be accessed by all the threads
struct SharedGameData {
    std::atomic<GameState> gameState{GameState::RUNNING};
    std::atomic<int> score{0};
    std::atomic<int> lives{3};
    std::atomic<int> currentLevel{1};
    std::atomic<bool> redrawNeeded{true};
    // info about player and toxins



};

// defined in main.cpp
extern SharedGameData g_sharedData;
extern std::mutex g_displayMutex;
extern std::atomic<bool> gameRunning;

#endif