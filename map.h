#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "Wall.h"
#include "Cookie.h"
#include <vector>

class Map{
private:
    static const int WIDTH = 22;
    static const int HEIGHT = 22;
    char grid[HEIGHT][WIDTH];
    std::vector<Wall> walls;
    std::vector<Cookie> cookies;
     
public:
    Map();
    // map adjustment
    void initializeLevel(int level = 1);
    void addWall(const Wall& wall);
    void addCookie(const Cookie& cookie);
    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);
    void clearCell(int x, int y);
    void display() const;
    // movement validation
    bool isValidMove(int x, int y) const;
    // map info fetch
    bool isEdge(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isCookie(int x, int y) const;
    int getWidth() const {return WIDTH;}
    int getHeight() const {return HEIGHT;}

    const std::vector<Wall>& getWall() const{return walls;}
    const std::vector<Cookie>& getCookies() const{return cookies;}
};
#endif