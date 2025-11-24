#include "player.h"
#include "map.h"
#include <iostream>

Player::Player() 
    : Component(startX, startY, true),
      posX(11), posY(11), startX(11), startY(11), 
      lives(3), score(0), 
      currentDirection(Direction::RIGHT), 
      alive(true) {
}

void Player::moveUp() {
    std::lock_guard<std::mutex> lock(positionMutex);
    posY--;
    currentDirection = Direction::UP;
    //std::cout << "Player moved UP to (" << posX << ", " << posY << ")\n";
}

void Player::moveDown() {
    std::lock_guard<std::mutex> lock(positionMutex);
    posY++;
    currentDirection = Direction::DOWN;
    //std::cout << "Player moved DOWN to (" << posX << ", " << posY << ")\n";
}

void Player::moveLeft() {
    std::lock_guard<std::mutex> lock(positionMutex);
    posX--;
    currentDirection = Direction::LEFT;
    //std::cout << "Player moved LEFT to (" << posX << ", " << posY << ")\n";
}

void Player::moveRight() {
    std::lock_guard<std::mutex> lock(positionMutex);
    posX++;
    currentDirection = Direction::RIGHT;
    //std::cout << "Player moved RIGHT to (" << posX << ", " << posY << ")\n";
}

void Player::move(Direction direction, const Map& map){
    int newX = this->posX;
    int newY = this->posY;
    switch(direction){
        case Direction::UP:
            newY--;
            break;
        case Direction::DOWN:
            newY++;
            break;
        case Direction::LEFT:
            newX--;
            break;
        case Direction::RIGHT:
            newX++;
            break;
        default:
            break;
    }
    if(isValidMove(newX, newY, map)){
        std::lock_guard<std::mutex> lock(positionMutex);
        this->posX = newX;
        this->posY = newY;
        this->currentDirection = direction;
    }
}

void Player::resetPosition() {
    std::lock_guard<std::mutex> lock(positionMutex);
    posX = startX;
    posY = startY;
    currentDirection = Direction::RIGHT;
    alive = true;
    //std::cout << "Player reset to start position (" << posX << ", " << posY << ")\n";
}

void Player::loseLife() {
    lives--;
    alive = false;
    //std::cout << "Player lost a life! Remaining: " << lives << "\n";
    
    if (lives <= 0) {
        //std::cout << "GAME OVER - No lives remaining!\n";
        gameRunning = false;
    } else {
        respawn();
    }
}

void Player::respawn() { 
    resetPosition();
}

bool Player::isValidMove(int newX, int newY, const Map& map) const {
    return map.isValidMove(newX, newY);
}


int Player::getX() const {
    std::lock_guard<std::mutex> lock(positionMutex);
    return posX;
}

int Player::getY() const {
    std::lock_guard<std::mutex> lock(positionMutex);
    return posY;
}

Position Player::getPosition() const{
    std::lock_guard<std::mutex> lock(positionMutex);
    return Position(posX, posY);
}

int Player::getLives() const {
    return lives.load();
}

int Player::getScore() const {
    return score.load();
}

Direction Player::getCurrentDirection() const {
    return currentDirection.load();
}

bool Player::isAlive() const {
    return alive.load();
}

void Player::setPosition(int x, int y) {
    std::lock_guard<std::mutex> lock(positionMutex);
    posX = x;
    posY = y;
}

void Player::addScore(int points) {
    score += points;
    std::cout << "Score +" << points << "! Total: " << score << "\n";
}
