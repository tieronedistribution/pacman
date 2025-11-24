#ifndef PLAYER_H
#define PLAYER_H

#include <atomic>
#include <mutex>
#include "common.h"
#include "component.h"

class Map;

class Player: public Component {
public:
   
    Player();
    ~Player() = default;
    
 
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void move(Direction dir, const Map& map);
    
  
    void resetPosition();
    void loseLife();
    void respawn();
    

    int getX() const;
    int getY() const;
    int getLives() const;
    int getScore() const;
    Direction getCurrentDirection() const;
    bool isAlive() const;
    Position getPosition() const;
    

    void setPosition(int x, int y);
    void addScore(int points);
    
    
    bool isValidMove(int newX, int newY, const Map& map) const;
    std::string getType() const override{return "Player";}

private:

    int posX, posY;
    int startX, startY;  
    std::atomic<int> lives;
    std::atomic<int> score;
    std::atomic<Direction> currentDirection;
    std::atomic<bool> alive;
    
  
    mutable std::mutex positionMutex;
};

#endif 
