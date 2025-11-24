#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "player.h"
#include "map.h"
#include <atomic>
#include <thread>

class InputHandler {
public:
    InputHandler(Player& player, Map& map, std::atomic<bool>& gameRunning);
    ~InputHandler();
    
    void startInputThread();
    void stopInputThread();
    void keypress(); 

private:
    Player& playerRef;
    Map& gameMap;
    std::atomic<bool>& gameRunning;
    std::atomic<bool> inputThreadRunning;
    std::thread inputThread;
    
    void processInput();
};

#endif 
