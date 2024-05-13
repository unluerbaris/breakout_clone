#include "Ball.h"
#include <iostream>

Ball::Ball(float xPos, float yPos, int radius)
{
    this->position = Vector2(xPos, yPos);
    this->velocity = Vector2(0.0, 0.0);
    this->radius = radius;
    std::cout << "ball is created" << std::endl;
}

Ball::~Ball()
{
   std::cout << "ball is destroyed" << std::endl;
}

void Ball::Move(float deltaTime)
{
    this->position.x += this->velocity.x * deltaTime;
    this->position.y += this->velocity.y * deltaTime;
}