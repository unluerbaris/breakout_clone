#include "Ball.h"
#include <iostream>

Ball::Ball(float xPos, float yPos, int radius)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->radius = radius;
    std::cout << "ball is created" << std::endl;
}

Ball::~Ball()
{
   std::cout << "ball is destroyed" << std::endl;
}