#include "inputhandler.h"
#include <iostream>
#include <conio.h>  
#include <chrono>

#ifdef _WIN32
    #include <conio.h>
#else

    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    
    int kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;
        
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        
        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        
        return 0;
    }
#endif

InputHandler::InputHandler(Player& player, Map& map, std::atomic<bool>& gameRunning)
    : playerRef(player), gameMap(map), gameRunning(gameRunning), inputThreadRunning(false) {
}

InputHandler::~InputHandler() {
    stopInputThread();
}

void InputHandler::startInputThread() {
    inputThreadRunning = true;
    inputThread = std::thread(&InputHandler::keypress, this);
    std::cout << "Input handler thread started\n";
}

void InputHandler::stopInputThread() {
    inputThreadRunning = false;
    if (inputThread.joinable()) {
        inputThread.join();
        std::cout << "Input handler thread stopped\n";
    }
}

void InputHandler::keypress() {
    while (inputThreadRunning && gameRunning) {
        processInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    }
}

void InputHandler::processInput() {
    if (!kbhit()) return;
    
    char ch = getch();
    int currentX = playerRef.getX();
    int currentY = playerRef.getY();
    
    switch (ch) {
        case 'w': case 'W':  
            if (playerRef.isValidMove(currentX, currentY - 1, gameMap)) {
                playerRef.moveUp();
            }
            break;
            
        case 's': case 'S':  
            if (playerRef.isValidMove(currentX, currentY + 1, gameMap)) {
                playerRef.moveDown();
            }
            break;
            
        case 'a': case 'A':  
            if (playerRef.isValidMove(currentX - 1, currentY, gameMap)) {
                playerRef.moveLeft();
            }
            break;
            
        case 'd': case 'D':  
            if (playerRef.isValidMove(currentX + 1, currentY, gameMap)) {
                playerRef.moveRight();
            }
            break;
            
        case 'q': case 'Q':  
            gameRunning = false;
            std::cout << "Quit game requested\n";
            break;
            
        case 27: 
            gameRunning = false;
            std::cout << "ESC pressed - quitting game\n";
            break;
            
        default:
            
            break;
    }
}
