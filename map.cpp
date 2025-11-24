#include "Map.h"
#include <iostream>

// map components:
// edge : +
// wall : =
// cookies : .
// toxins : #
// player : @


Map::Map(){
    initializeLevel(1); //
}

void Map::initializeLevel(int level){ //
    // initialize the map with edges and cookies only
    for (int y = 0; y < HEIGHT; y++) {  
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH-1 || y == 0 || y == HEIGHT-1) {
                grid[y][x] = '+'; // edge
            }
        }
    }
}

void Map::addWall(const Wall& wall){
    grid[wall.getY()][wall.getX()] = '='; //wall
}

void Map::addCookie(const Cookie& cookie){
    grid[cookie.getY()][cookie.getX()] = '.'; //cookie
}

bool Map::isValidMove(int x, int y) const{
    // check if the movement is valid
    return x > 0 && x < WIDTH && y > 0 && y < HEIGHT && !isWall(x, y);
}

bool Map::isEdge(int x, int y) const{
    // check if the component at the position is a edge
    return getCell(x, y) == '+';
}

bool Map::isWall(int x, int y) const{
    // check if the component at the position is a wall
    return getCell(x, y) == '=';
}

bool Map::isCookie(int x, int y) const{
    // check if the component at the position is a cookie
    return getCell(x, y) == '.';
}

char Map::getCell(int x, int y) const{
    // return the component at that position
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT){
        return grid[y][x];
    }
    return ' '; // if out of range then return space
}
 
void Map::setCell(int x, int y, char value){
    // fulfill the map with the 'value' passed in
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT){
        grid[y][x] = value;
    }
}

void Map::clearCell(int x, int y){
    // fulfill the map with " "
    setCell(x, y, ' ');
}

void Map::display() const{
    // display the map
    using std::cout;

    std::lock_guard<std::mutex> lock(g_displayMutex);

    system("clear");
    
    cout << "=== PACMAN === Score: " << g_sharedData.score << std::endl;
    cout << " Lives left: " << g_sharedData.lives << std::endl;
    cout << " Level: " << g_sharedData.currentLevel << "\n\n";
    
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            cout << grid[y][x] << ' ';
        }
        cout << '\n';
    }
    cout << std::endl;
}