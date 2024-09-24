#include "Paddle.h"
#include <iostream>

Paddle::Paddle(int xPos, int yPos, int width, int height, int speed)
{
    this->position = Vector2(xPos, yPos);
    this->velocity = Vector2(0.0, 0.0);
    this->width = width;
    this->height = height;
    this->speed = speed;
    std::cout << "paddle is created" << std::endl;
}

Paddle::~Paddle()
{
   std::cout << "paddle is destroyed" << std::endl;
}

void Paddle::UpdatePosition(float deltaTime)
{
    this->position.x += this->velocity.x * deltaTime;
}