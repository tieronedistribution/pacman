#ifndef WALL_H
#define WALL_H

#include <string>
#include "component.h"

// this class was changed to be derived from the component class
class Wall: public Component{
    int x, y;
public:
    Wall(int xPos, int yPos): Component(xPos, yPos, false){}

    int getX() const;
    int getY() const;
    std::string getType() const override{return "Wall";}
};

#endif