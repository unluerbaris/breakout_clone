#include "Paddle.h"
#include <iostream>

Paddle::Paddle(float xPos, float yPos, int width, int height)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    std::cout << "paddle is created" << std::endl;
}

Paddle::~Paddle()
{
   std::cout << "paddle is destroyed" << std::endl;
}