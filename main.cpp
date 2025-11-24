#include "GameEngine.h"
#include <iostream>
#include <chrono>

int main(){
    using std::cout;
    using std::endl;
    cout << "=== Pacman ===" << endl;
    // 60fps
    int FRAMERATE = 60;
    
    try {
        // create gameengine object
        GameEngine gameEngine;
        
        // level selection
        //gameEngine.select_level();
        //after level selection, sleep for 5 seconds
        //cout << "game will start in 5 second ..." << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(5));

        // initialize the game
        gameEngine.startGame();
        
        // main loop
        while(gameEngine.isGameRunning()){
            // check if game failed
            if (g_sharedData.lives <= 0){
                gameEngine.setGameState(GameState::GAME_OVER);
                break;
            }
            if(!gameEngine.isGameRunning()){
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FRAMERATE));
        }
        
        // processes when game ends
        system("clear");
        cout << "\n\n\n=== GAME OVER ===" << endl;
        cout << "Final Score: " << g_sharedData.score << endl;
        
    } catch (const std::exception& e){ // exception handles
        std::cerr << "Game crashed with error: " << e.what() << endl;
        return 1;
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}