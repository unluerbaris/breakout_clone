#include "Brick.h"
#include <iostream>

Brick::Brick(int xPos, int yPos, int width, int height)
{
    this->position = Vector2(xPos, yPos);
    this->width = width;
    this->height = height;
    std::cout << "brick is created" << std::endl;
}

Brick::~Brick()
{
   std::cout << "brick is destroyed" << std::endl;
}