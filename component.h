#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>

class Component {
protected:
    int x, y;
    bool movable;

public:
    Component(int xPos, int yPos, bool isMovable)
        : x(xPos), y(yPos), movable(isMovable) {}

    virtual ~Component() = default;
    virtual std::string getType() const = 0;

    int getX() const {return x;}
    int getY() const {return y;}
    void setPosition(int newX, int newY){
        x = newX;
        y = newY;
    }
    // fetch movability
    bool isMovable() const {return movable;}
};

#endif